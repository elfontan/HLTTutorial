
# HLT Photon studies

## Setup
Setup the release, import HLTrigger package, compile
```
cmsrel CMSSW_15_0_3_patch1
cd CMSSW_15_0_3_patch1/src
cmsenv
git cms-addpkg HLTrigger/Configuration
scram b -j 8
```
Creat a proxy (to access remote files)

```
voms-proxy-init --voms cms --valid 168:00
```

Clone this repository, and compile

```
git clone https://github.com/elfontan/HLTTutorial.git 
scram b -j4
```

Obtain the configuration file from the dedicated menu with the following recipe:
```
hltGetConfiguration --cff /users/lathomas/Photon2025/HLTDiphotonLowMass/V14 --globaltag auto:run3_data_prompt --path HLTriggerFirstPath,HLTriggerFinalPath,HLT_Ele5_PassFilters_v1,HLT_Diphoton30_18_R9IdL_AND_HE_AND_IsoCaloId_v11,HLT_Ele32_WPTight_Gsf_v25,HLT_Photon40EB_TightID_TightIso_v3,HLT_Photon45EB_TightID_TightIso_v3,HLT_Diphoton15_10_TightID_ECALTrackIsoDr0p2_EBEB_v11,HLT_Diphoton15_10_TightID_ECALTrackIsoDr0p2to0p4_EBEB_v11 --unprescale &> HLT_DiphotonLowMass_cff.py
```
and move it in the `HLTrigger/Configuration/python/` area.

The `customhltnano.py` is provided in the repository. In case it is needed to recreate it, copy the menu configuration in `Configuration/python` as `HLT_Custom_cff.py`:
```
cp  HLTTutorial/TriggerAnalyzerRAWMiniAOD/python/HLT_2025DiphotonPathPUCorr_cff.py HLTrigger/Configuration/python/HLT_Custom_cff.py
```
and run cmsDriver command to build the chain down to nanoAOD:
```
cmsDriver.py customHLT --conditions auto:run3_data_prompt -s RAW2DIGI,L1Reco,HLT:Custom,PAT,NANO:@PHYS --datatier NANOAOD --eventcontent NANOAOD --data --process customhltnano --scenario pp --era Run3 --customise Configuration/DataProcessing/RecoTLR.customisePostEra_Run3 -n 100 --filein /store/data/Run2024I/EGamma0/RAW-RECO/ZElectron-PromptReco-v2/000/386/694/00000/05ad2e1f-93d3-4e3e-98a5-e5c911bc410b.root --fileout file:out.root --python_filename=customhltnano.py
```
then modify the `customhltnano.py` configuration to run also the specific photon ntupliser:
```
process.demo = cms.EDAnalyzer('TriggerAnalyzerRAWMiniAOD',                                                                      
                              UseMINIAOD = cms.bool(True)                                                                                                
)                                                                         
process.TFileService = cms.Service("TFileService",                                                                               
                                   fileName = cms.string( "out_nanoCustom.root" )                                                                        
                                   )                                                                              
process.demo_step = cms.EndPath(process.demo)
```
by also adding in `process.schedule.extend([...])` also `process.demo_step`.

Execute the code 
```
cmsRun customhltnano.py
```


## What the code does  
The code above does two things:
- Rerun a HLT menu containing a single electron path, a single photon path, and a dummy single photon path with very low thresholds (`HLT_2025DiphotonPathPUCorr_cff.py`). This file is produced with the usual `hltGetConfiguration` command.
- Run an EDAnalyzer (```TriggerAnalyzerRAWMiniAOD```) that creates a flat tree containing information related to HLT photons generated when running `HLT_Photon50EB_TightID_TightIso`, and to the subset of these HLT photons that are matched to probe offline electrons from an offline Z->ee selection. 

The code can run on RAW only (for rate studies), or on RAW+MINIAOD (for efficiency studies with Z->ee reconstructed offline). Mind the `UseMINIAOD` boolean in `rerunHLTandAnalyzer.py`.

## Output
The output tree contains mostly: 
- HLT bit decisions, either original or rerun, the former contains the suffix `ORIG`.
- A collection of variables related to probe electrons. They are labelled by the `probe_ele` prefix. In addition to the electron pt, eta, phi, one finds in particular the ID/ISO variables of the possibly matched HLT photon (dummy values when no HLT photon is found). 
- A collection of variables related to HLT photons. They are labelled by the `hltphoton` prefix.
- A collection of variables related to offline photons. They are labelled by the `_ph`prefix. 

Notice that because ID/ISO variables are computed sequentially and only if the HLT photon passes the previous filters in`HLT_Photon50EB_TightID_TightIso` , one will find less and less HLT photons. 
To overcome this, one could disable all the filters in the configuration of `HLT_Photon50EB_TightID_TightIso`. 
