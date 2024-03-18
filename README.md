
# HLT Photon studies

## Setup
Setup the release, import HLTrigger package, compile
```
cmsrel CMSSW_14_0_0
cd CMSSW_14_0_0/src
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
git clone https://github.com/lathomas/HLTTutorial.git -b PhotonStudies 
scram b -j4
```

```
mv  HLTTutorial/TriggerAnalyzerRAWMiniAOD/python/HLT_TutoElePhotonWPTight_cff.py HLTrigger/Configuration/python/.
```
Execute the code 

```
cmsRun HLTTutorial/TriggerAnalyzerRAWMiniAOD/python/rerunHLTandAnalyzer.py
```


## What the code does  
The code above does two things:
- Rerun a HLT menu containing a single electron and single photon path (`HLT_TutoElePhotonWPTight_cff.py`). This file is produced with the usual `hltGetConfiguration` command.
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
