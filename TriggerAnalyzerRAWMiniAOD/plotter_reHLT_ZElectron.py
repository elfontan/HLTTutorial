import ROOT
import os, glob, math
import CMSGraphics, CMS_lumi
from ROOT import gStyle
ROOT.gROOT.SetBatch()            
ROOT.gStyle.SetOptStat(0)                                         
ROOT.gStyle.SetOptTitle(0)

# Inputs
# ----------------------
repo_path = "/eos/user/e/elfontan/DiPhotonAnalysis/Run3_Trigger/reHLT_ZElectron/condor/reHLT_ZElectron_1745272025/"
file_pattern = os.path.join(repo_path, "out_nanoCustom_*.root")
#repo_path = "/eos/user/e/elfontan/DiPhotonAnalysis/Run3_Trigger/reHLT_ZElectron/condor/TEST/"
#file_pattern = os.path.join(repo_path, "*root")
root_files = glob.glob(file_pattern)
output_dir = "/eos/user/e/elfontan/www/RUN3_LowMassDiPhoton/ZElectron/HISTOS_PtEtaBins/"

# Variables and ranges
# --------------------
variables = {
    "hoe":      {"title": "H over E",   "nbins": 200, "xmin": -2.,   "xmax": 2., "xlabel": r"H/E", "log": False},
    "hcaliso":  {"title": "HCAL Iso",   "nbins": 200, "xmin": -10.,   "xmax": 10., "xlabel": r"HCal isolation", "log": False},
    "customecaliso":  {"title": "Custom ECAL Iso",   "nbins": 100, "xmin": -2.,   "xmax": 6., "xlabel": r"Custom ECal isolation", "log": False},
    "customecaliso2":  {"title": "Custom ECAL Iso (2)",   "nbins": 100, "xmin": -2.,   "xmax": 6., "xlabel": r"Custom ECal isolation (2)", "log": False},
    "custom1trackiso": {"title": "Custom Track Iso",  "nbins": 100, "xmin": -4., "xmax": 6., "xlabel": r"Custom Track isolation", "log": False},
    "custom2trackiso": {"title": "Custom Track Iso (2)",  "nbins": 100, "xmin": -4., "xmax": 6., "xlabel": r"Custom Track isolation (2)", "log": False},
    ####"ecaliso":  {"title": "ECAL Iso",   "nbins": 100, "xmin": -2.,   "xmax": 6., "xlabel": r"ECal isolation", "log": False},
    ####"trackiso": {"title": "Track Iso",  "nbins": 100, "xmin": -4., "xmax": 6., "xlabel": r"Track isolation", "log": False},
    ####"hoeXe":      {"title": "H part of Hover E",   "nbins": 200, "xmin": -2.,   "xmax": 100., "xlabel": r"H/E x E", "log": False},
}

# Define eta bins and effective areas
# -----------------------------------
ea_eta_bins = [0.0, 1.0, 1.479, 2.1]
ea_values = {
    "hoe": [0.066, 0.14, 0.3, 0.5],
    "hcal": [0.26, 0.32, 0.4, 0.5],
    "ecaliso1": [0.1, 0.08, 0.06, 0.06],
    "ecaliso2": [0.24, 0.2, 0.16, 0.14],
    "1trackiso": [0.14, 0.14, 0.16, 0.16],
    "2trackiso": [0.2, 0.2, 0.2, 0.2],
    ####"ecal": [0.1, 0.08, 0.06, 0.06],
    ####"track": [0.03, 0.04, 0.114, 0.032],
    ####"hoeXe": [0.066, 0.14, 0.3, 0.5]
}
ea_info = {}  # New dict to store ea values and formulas per (var, pt_eta_key)

# Initialize histograms for three pt ranges
# -----------------------------------------
histos = {}
pt_eta_ranges = ["20-50_EB_0-1", "20-50_EB_1-1p5", "20-50_EE_1p5-2p1", "20-50_EE_2p1-2p5", "10-20_EB_0-1", "10-20_EB_1-1p5", "10-20_EE_1p5-2p1", "10-20_EE_2p1-2p5", "5-10_EB_0-1", "5-10_EB_1-1p5", "5-10_EE_1p5-2p1", "5-10_EE_2p1-2p5"]

for var, cfg in variables.items():
    histos[var] = {}
    for pt_eta in pt_eta_ranges:
        hist = ROOT.TH1F(f"{var}_{pt_eta}", f"{cfg['title']} ({pt_eta})", cfg["nbins"], cfg["xmin"], cfg["xmax"])
        hist.Sumw2()
        histos[var][pt_eta] = hist

# Loop over ROOT files and fill histograms
for root_file in root_files:
    print("Processing:", root_file)
    file = ROOT.TFile.Open(root_file, "READ")
    if not file or file.IsZombie():
        print(f"Skipping corrupted file: {root_file}")
        continue

    tree = file.Get("demo/tree")
    if not tree:
        print(f"No 'demo/tree' found in {root_file}")
        file.Close()
        continue

    for i in range(tree.GetEntries()):
        tree.GetEntry(i)
        if not tree.probe_ele_pt or tree.probe_ele_pt.size() == 0:
            continue  

        for pt, eta in zip(tree.probe_ele_pt, tree.probe_ele_eta):
            if 5 <= pt < 10:
                pt_range = "5-10"
            elif 10 <= pt < 20:
                pt_range = "10-20"
            elif 20 <= pt < 50:
                pt_range = "20-50"
            else:
                continue
            
            #region = "EB" if abs(eta) <= 1.479 else "EE"
            if abs(eta) <= 1.0:
                region = "EB_0-1"
            elif (abs(eta) > 1.0 and abs(eta) <= 1.479):
                region = "EB_1-1p5"
            elif (abs(eta) > 1.479 and abs(eta) <= 2.1):
                region = "EE_1p5-2p1"
            elif (abs(eta) > 2.1 and abs(eta) <= 2.5):
                region = "EE_2p1-2p5"

            pt_eta_key = f"{pt_range}_{region}"
            
            # Find the index of the eta bin
            eta_index = next((i for i in range(len(ea_eta_bins)-1) if ea_eta_bins[i] <= abs(eta) < ea_eta_bins[i+1]), len(ea_eta_bins)-2)
        
            for var, cfg in variables.items():
                value = getattr(tree, f"probe_ele_ele32wptight_{var}_HLT")
                for val in value:
                    ea = 0

                    formula_str = ""
                    if var == "hoe":
                        ea = ea_values["hoe"][eta_index]
                        #print(f"eta = {eta:.3f}, bin = [{ea_eta_bins[eta_index]}, {ea_eta_bins[eta_index+1]}), ea = {ea}")
                        val_uncorr = (val * pt * math.cosh(eta) - tree.hlt_rho * ea) / (pt * math.cosh(eta))
                        formula_str = r"(H/E $\cdot p_T$ - $\rho$ $\cdot$ {ea:.3f}) / $p_T$".format(ea=ea)
                    #elif var == "hoeXe":
                    #    ea = ea_values["hoeXe"][eta_index]
                    #    val_uncorr = (val * pt * math.cosh(eta) - tree.hlt_rho * ea) / (pt * math.cosh(eta))
                    #    formula_str = r"(H/E $\cdot$ E - $\rho$ $\cdot$ {ea:.3f}) / E".format(ea=ea)
                    else:
                        if "hcal" in var:
                            ea = ea_values["hcal"][eta_index]
                        elif "ecaliso1" in var:
                            ea = ea_values["ecaliso1"][eta_index]
                        elif "ecaliso2" in var:
                            ea = ea_values["ecaliso2"][eta_index]
                        elif "1trackiso" in var:
                            ea = ea_values["1trackiso"][eta_index]
                        elif "2trackiso" in var:
                            ea = ea_values["2trackiso"][eta_index]
                        #elif "ecal" in var:
                        #    ea = ea_values["ecal"][eta_index]
                        #elif "trackiso" in var:
                        #    ea = ea_values["track"][eta_index]
                        else:
                            ea = 0.0                            

                        formula_str = r"${var} \cdot p_T - \rho \cdot {ea:.3f}$".format(var=var, ea=ea)
                        val_uncorr = val * pt - tree.hlt_rho * ea
                        

                    # Store only the first time for each var-bin key
                    ea_info.setdefault(var, {}).setdefault(pt_eta_key, formula_str)

                    histos[var][pt_eta_key].Fill(val_uncorr)

                            
    file.Close()

    
import matplotlib.pyplot as plt
import mplhep
import numpy as np

mplhep.style.use("CMS")  

colors = {
    # 5-10 GeV
    "5-10_EB_0-1":        "royalblue",
    "5-10_EB_1-1p5":      "cornflowerblue",
    "5-10_EE_1p5-2p1":    "skyblue",
    "5-10_EE_2p1-2p5":    "lightblue",

    # 10-20 GeV
    "10-20_EB_0-1":       "mediumseagreen",
    "10-20_EB_1-1p5":     "mediumaquamarine",
    "10-20_EE_1p5-2p1":   "springgreen",
    "10-20_EE_2p1-2p5":   "palegreen",

    # 20-50 GeV
    "20-50_EB_0-1":       "tomato",
    "20-50_EB_1-1p5":     "lightsalmon",
    "20-50_EE_1p5-2p1":   "coral",
    "20-50_EE_2p1-2p5":   "moccasin",
}

for var, cfg in variables.items():
    for pt_eta_key, hist in histos[var].items():
        # --- Regular Histogram Plot ---
        fig, ax = plt.subplots(figsize=(10, 8))

        values = [hist.GetBinContent(i+1) for i in range(hist.GetNbinsX())]
        bins = [hist.GetBinLowEdge(i+1) for i in range(hist.GetNbinsX()+1)]
        bin_centers = [(bins[i] + bins[i+1])/2 for i in range(len(bins)-1)]

        # Compute Y-axis max with headroom
        max_val = max(values) * 1.5 if max(values) > 0 else 1.0

        ax.step(bin_centers, values, where="mid",
                label=pt_eta_key,
                linewidth=1.5,
                color=colors.get(pt_eta_key, "black"))

        ax.set_xlabel(cfg["xlabel"], fontsize=24)
        ax.set_ylabel("Entries", fontsize=24)
        ax.set_xlim(cfg["xmin"], cfg["xmax"])
        ax.set_ylim(0.1 if cfg["log"] else 0, max_val)
        if cfg["log"]:
            ax.set_yscale("log")

        mplhep.cms.label("Preliminary", data=True, rlabel="2024 (13.6 TeV)", loc=1)

        bin_label = f"{pt_eta_key}"
        #bin_label = f"{pt_range} GeV ({region})"
        ax.text(0.95, 0.5, f"{bin_label}",
                transform=ax.transAxes,
                fontsize=25,
                style='italic',
                ha='right',  # horizontal alignment
                va='center') # vertical alignment

        # Add formula and EA used
        formula_str = ea_info.get(var, {}).get(pt_eta_key, "")
        if formula_str:
            ax.text(0.95, 0.43, formula_str,
                    transform=ax.transAxes,
                    fontsize=16,
                    ha='right',
                    va='center')
            
        plt.tight_layout()
        plt.savefig(os.path.join(output_dir, f"{var}_{pt_eta_key}_hist.png"), dpi=300)
        plt.savefig(os.path.join(output_dir, f"{var}_{pt_eta_key}_hist.pdf"), dpi=300)
        plt.close()

        # --- Reverse Cumulative Plot ---
        fig, ax = plt.subplots(figsize=(10, 8))
        cumul = hist.GetCumulative()

        if hist.GetEntries() > 0:
            cumul.Scale(1. / hist.GetEntries())
    
        values = [cumul.GetBinContent(i+1) for i in range(cumul.GetNbinsX())]
        total = cumul.GetBinContent(cumul.GetNbinsX())
        if total > 0:
            values = [v / total for v in values]
        bins = [cumul.GetBinLowEdge(i+1) for i in range(cumul.GetNbinsX()+1)]
        bin_centers = [(bins[i] + bins[i+1])/2 for i in range(len(bins)-1)]

        ax.step(bin_centers, values, where="mid",
                label=pt_eta_key,
                linewidth=1.5,
                color=colors.get(pt_eta_key, "black"))

        ax.set_xlabel(cfg["xlabel"], fontsize=24)
        ax.set_ylabel("Fraction with value > x", fontsize=24)
        ax.set_xlim(cfg["xmin"], cfg["xmax"])
        ax.set_ylim(0.0, 1.3)
        ax.set_yscale("linear")
        #ax.set_ylim(1e-4, 1.1)
        #ax.set_yscale("log")

        mplhep.cms.label("Preliminary", data=True, rlabel="2024 (13.6 TeV)", loc=1)

        bin_label = f"{pt_eta_key}"
        #bin_label = f"{pt_range} GeV ({region})"
        ax.text(0.95, 0.5, f"{bin_label}",
                transform=ax.transAxes,
                fontsize=25,
                style='italic',
                ha='right',  # horizontal alignment
                va='center') # vertical alignment

        plt.tight_layout()
        plt.savefig(os.path.join(output_dir, f"{var}_{pt_eta_key}_reverse_cumul.png"), dpi=300)
        plt.savefig(os.path.join(output_dir, f"{var}_{pt_eta_key}_reverse_cumul.pdf"), dpi=300)
        plt.close()


# Save all histograms to a ROOT file for later reuse
output_root = ROOT.TFile("histos_per_bin.root", "RECREATE")
for var in variables:
    output_root.mkdir(var)
    output_root.cd(var)
    for pt_eta_key, hist in histos[var].items():
        hist.SetDirectory(0)  # Detach from any file (safety)
        hist.Write(f"{pt_eta_key}")  # Save with the pt_eta_key as name
output_root.Close()

print("Histograms saved to histos_per_bin.root")

#f = ROOT.TFile("histos_per_bin.root")
#hist = f.Get("hoe/10-20_EB")  # example
