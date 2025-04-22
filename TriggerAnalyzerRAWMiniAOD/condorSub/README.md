# Ntuple production in condor

## 1. Customization of the submission file
In the `condorSub` subfolder, customize the HTCondor submission script `condor_sub.py` according to your needs:
- `nEvents`: number of events to process
- `nJobs`: number of jobs for the splitting (corresponding to the number of files by default)
- `fileList`: list of GEN-SIM-RAW files 
- `jobScript`: bash script containing the cmsRun command. NOTE: the default is `cmsRun.sh`.
- `eosDir`: output folder for batch jobs (user must have write permissions)
- `jobName`: name of the directory created in eosDir and locally

## 2. Submit the production
Some remaining steps before submitting:
```
scram b -j 8
voms-proxy-init --voms cms --valid 168:00 -out $HOME/private/.proxy
export X509_USER_PROXY=$HOME/private/.proxy
```

Finally, launch the production with
```
python3 condor_sub.py
```

## 3. Check the output directory
When all jobs finished to run, check the output directory, identify files corresponding to failed jobs looking at the size of the file, and delete them:
```
find . -name "*.root" -size -10k
find . -name "*.root" -size -10k -delete
```

  
