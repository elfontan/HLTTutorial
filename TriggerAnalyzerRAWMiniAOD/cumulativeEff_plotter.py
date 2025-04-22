import ROOT
import os
import matplotlib.pyplot as plt
import numpy as np
import mplhep                                                                                                                    


# Open the ROOT file
rootfile = ROOT.TFile.Open("setOfHistos_per_bin.root")
outdir = "/eos/user/e/elfontan/www/RUN3_LowMassDiPhoton/ZElectron/HISTOS_PtEtaBins/CumulativePlots/"
os.makedirs(outdir, exist_ok=True)

# Target efficiencies
eff_lines = [0.90, 0.99]
line_colors = ["orangered", "orange"]       # horizontal lines
vline_colors = ["royalblue", "skyblue"]     # vertical lines

# Get list of directories (variables)
keys = [k.GetName() for k in rootfile.GetListOfKeys()]

for var in keys:
    dir = rootfile.Get(var)
    hist_keys = [k.GetName() for k in dir.GetListOfKeys()]
    
    for hname in hist_keys:
        hist = dir.Get(hname)
        hist = hist.Clone()  
        hist.SetDirectory(0)

        # Get cumulative from the right (efficiency curve)
        # ------------------------------------------------
        #cum = hist.GetCumulative(False)  # False = from right
        cum = hist.GetCumulative() 

        # Normalize cumulative to max = 1
        total = cum.GetBinContent(cum.GetNbinsX())
        if hist.GetEntries()>0:
            cum.Scale(1.0 / total)

        x_vals = np.array([cum.GetBinCenter(i) for i in range(1, cum.GetNbinsX() + 1)])
        y_vals = np.array([cum.GetBinContent(i) for i in range(1, cum.GetNbinsX() + 1)])

        # Plot
        plt.figure(figsize=(10, 8))
        plt.plot(x_vals, y_vals, label="Cumulative", color="black")

        # Draw efficiency lines and vertical cuts
        for i, eff in enumerate(eff_lines):
            idx = np.searchsorted(y_vals, eff)
            if idx >= len(x_vals):
                continue
            cut_val = x_vals[idx]
            
            plt.axhline(eff, color=line_colors[i], linestyle="--", linewidth=1)
            plt.axvline(cut_val, color=vline_colors[i], linestyle="--", linewidth=1)
            plt.text(cut_val, -0.8 + eff, f"{cut_val:.3f}",
                     rotation=0, va="bottom", ha="right", color=vline_colors[i], fontsize=14)

        #for eff in eff_lines:
        #    idx = np.searchsorted(y_vals, eff)
        #    if idx >= len(x_vals):
        #        continue
        #    cut_val = x_vals[idx]
        #    plt.axhline(eff, color="red", linestyle="--", linewidth=1)
        #    plt.axvline(cut_val, color="blue", linestyle="--", linewidth=1)
        #    plt.text(cut_val, -0.8 + eff, f"{cut_val:.3f}", rotation=0, va="bottom", ha="right", color="blue")

        mplhep.style.use("CMS")
        mplhep.cms.label("Preliminary", data=True, rlabel="2024 (13.6 TeV)", loc=1)
        ax = plt.gca()
        ax.set_xlabel(var, fontsize=24)
        ax.set_ylabel("Fraction with value > x", fontsize=24)
        
        # Right-side label for bin name (italic)
        ax.text(0.98, 0.95, hname.replace("_", " "),
                transform=ax.transAxes,
                fontsize=22,
                style='italic',
                ha='right', va='top')
    
        # Print cumulative values as table
        print(f"\nCumulative values for {var} - {hname}")
        print(f"{'Bin center':>12} | {'Fraction > x':>12}")
        print("-" * 27)
        for x, y in zip(x_vals, y_vals):
            print(f"{x:12.3f} | {y:12.5f}")
            
        plt.xlabel(var, fontsize=24)
        plt.ylabel("Fraction with value > x", fontsize=24)
        #plt.title(f"{var} - {hname}", fontsize=24)

        plt.ylim(0, 1.3)
        plt.grid(True, which="both", linestyle="--", alpha=0.3)
        plt.tight_layout()
        outnamepng = f"{outdir}/{var}_{hname.replace(';1','').replace(' ','_')}.png"
        outnamepdf = f"{outdir}/{var}_{hname.replace(';1','').replace(' ','_')}.pdf"
        plt.savefig(outnamepng, dpi=150)
        plt.savefig(outnamepdf, dpi=150)
        plt.close()

print(f"Done. Plots saved in '{outdir}'")
