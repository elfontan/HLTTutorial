# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: customHLT --conditions auto:run3_data_prompt -s RAW2DIGI,L1Reco,HLT:Custom --datatier NANOAOD --eventcontent NANOAOD --data --process customhltnano --scenario pp --era Run3 --customise Configuration/DataProcessing/RecoTLR.customisePostEra_Run3 -n 100 --filein file:/pnfs/iihe/cms/ph/sc4/store/data/Run2024I/EGamma0/RAW-RECO/ZElectron-PromptReco-v1/000/386/604/00000/64ffc9b9-f956-40ee-9cd3-5708c65b6605.root --fileout file:out.root --python_filename=customhltnano_HLTPh.py
import FWCore.ParameterSet.Config as cms

from Configuration.Eras.Era_Run3_cff import Run3

process = cms.Process('customhltnano',Run3)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
#process.load('HLTrigger.Configuration.HLT_Custom_cff')
#process.load('HLTrigger.Configuration.myhlt_HLTDiphotonLowMass_V6_cff')
process.load('HLTrigger.Configuration.HLT_DiphotonLowMass_cff')

process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.MessageLogger.cerr.FwkReport.reportEvery = 100

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1),
    output = cms.optional.untracked.allowed(cms.int32,cms.PSet)
)

# Input source
process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring(
#                                'file:/pnfs/iihe/cms/ph/sc4/store/data/Run2024I/EGamma0/RAW-RECO/ZElectron-PromptReco-v1/000/386/604/00000/83e85753-f40e-4b45-9056-66eda6cfa7ea.root',
#                                'file:/pnfs/iihe/cms/ph/sc4/store/data/Run2024I/Muon0/RAW-RECO/ZMu-PromptReco-v1/000/386/478/00000/01c0513b-d4fd-4cdd-8eed-c912bd28e64b.root',

#'file:/user/lathomas/TriggerDevRun3/MergedDiphotonDiele/HAHM_ZpToEE_M1VBF_INCLUSIVE_Leta1p22_LpT5_k1e_10_eps0p02_13p6TeV_GEN_RAW_SIM.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/061df7cf-d300-4142-8647-f97342a78852.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/0672b1b9-17d2-41cd-a0e7-f611d188206e.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/07e030c0-87fd-4087-a52f-5640df69bce0.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/07e3ec95-4cfa-4f86-92e8-4d69195a7397.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/09226fc0-60ca-46b1-abb8-d68e10ac5145.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/09908b50-3a9a-4bab-8c1e-9516568b4bc2.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/09d64eb7-1788-403a-8fea-a9830353bdf5.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/0a4de692-1ef2-45e8-a860-5324fb0badd0.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/0ac57bdb-907c-4383-8b00-a0e5bcfbb414.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/0ca560a8-988c-447a-9faf-01e11d5b2e3e.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/0cd1f654-37e9-42f5-8479-bca6917e06c5.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/0d48ff3e-2374-45b4-bf63-daa947d847e1.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/0d9aa92f-f114-438e-9c45-58d9493d7717.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/0eda254f-e0ad-4f45-98fb-726af4dc959d.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/0fa172db-e114-4813-ae5d-60e7bb2c9ece.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/114ae02b-a0f7-44ca-8978-84fa89329dbd.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/13256d67-a30c-42e1-acda-8cc7cd20e3d2.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/13480379-0e5a-40a7-88b7-d67aa85313d8.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/1357d447-d7eb-49f4-91a8-412394b98196.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/135d11b2-19ff-4c09-8b2b-de035e0c9c15.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/148745a4-c538-4d13-a600-9066b138b237.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/14f65875-cf86-4b2f-a710-4401b960233a.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/1544d644-3b6b-4e93-abaa-7a6fbcdde2a2.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/15fc6f5e-0efc-4061-bab3-390cc2874a34.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/16806136-c2ea-4304-a9dd-de86dc0d8879.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/168f0c99-ccbf-4514-b054-5099b447cceb.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/16a856d1-16d2-48f1-920a-38a0aeb3e4f7.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/16c11ea8-c5df-44dc-925a-ee031c8aceea.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/17310b3a-708d-472e-bbe4-a70246d63ecc.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/18138665-8106-4ae9-a1e3-b9996250dfbb.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/18bbb942-745f-4552-a5d9-1ef83aafcd09.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/18ddf344-7a4d-4b40-834c-5f3bb5978c48.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/18e54c98-abcc-40af-a608-ee6a4761fe8e.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/1941751c-da24-4ccc-bf80-04c7b17c3e92.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/197a8c48-410e-4f93-a913-6d2c8485bdee.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/19ca99d3-d246-48c0-a09d-451c251fa38c.root',
                                '/store/mc/Run3Winter24Digi/GluGluHToGG_M-10_TuneCP5_13p6TeV_amcatnloFXFX-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v9-v2/2830000/19fee85d-1345-4fc4-aabf-d96cf533ba8e.root',

                                '/store/mc/Run3Winter25Digi/DYto2E_Bin-1J-MEE-0p1to4-PtE-7-PtJ-15_TuneCP5_13p6TeV_madgraphMLM-pythia8/GEN-SIM-RAW/142X_mcRun3_2025_realistic_v7-v1/2530000/02522a8b-bccb-4362-9296-ab68f9427fd7.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/083c14f6-53e9-4ed8-895b-83f40d16093b.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/0f16d6e0-75ec-423c-a409-793030cf212d.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/17bf4fa9-809e-4ee2-838b-b5e0c8284991.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/19889bfd-c200-4d82-a31d-25cf208dea23.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/1c616122-780d-450f-b73d-cc4d829a1ee1.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/2c9cfd18-f310-46be-888b-bd85b2da3948.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/3121af09-d0ea-4866-b8d7-9ed144f11e8e.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/36cdf09e-98a3-4144-9fde-4c6b536cc254.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/398ce84d-045c-4768-be1e-399c3baf0b69.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/604fc983-d1bc-4c0d-a558-111194eb2328.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/60e503b9-0d76-4ad6-8905-fb594bac77af.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/64f63e57-e027-4f73-91e3-ca051077fb25.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/71a498a4-1dda-4ca7-8e22-9e9f4edb9c44.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/757e0bf3-f8fd-49ea-b56e-3e26f0418d24.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/7a642da8-6f58-4786-8965-f13e98d81888.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/7d6c0e3d-33fa-44ba-95c5-8368ed0c6e1f.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/7d753e04-e42f-428e-a083-186daa28a407.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/7f61f50e-de94-4fbc-b477-bf3a8bb7b1a1.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/80f38115-5a21-4b1f-b5c1-8de45eefc1d5.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/8846bf89-e182-4ad5-ba8c-0ed29c1cdaac.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/8b9ba363-6b24-4308-a54c-786a70ab56fd.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/9663931a-8abd-4637-8c82-e8467873cf0c.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/97979bdb-5c81-402a-b9be-28fd9abd74a7.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/990305c4-fa2e-466d-99b3-f496e2e6d804.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/99e529a0-6622-4f01-9abd-2a7a93e227b6.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/a72c0a03-0c42-40b9-9eae-5984af409810.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/a9e80fdd-41aa-4d52-a1f9-fc258f4ae060.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/acd04f39-f9a7-482a-a4d3-61dd407eb710.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/af724e0d-f9f7-418b-9a1f-2fbfcb9130cf.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/b1881cfc-fab2-4aef-afab-52f96a86c6ae.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/bb5f7d19-1cf1-4eef-b326-8934daffd8a5.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/c1ccd936-2c4d-4196-92c8-88ffaf771dfb.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/c3902f3b-8c76-4e56-9946-f6002ed2dbe7.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/c43c2e0c-e660-4409-87c5-ccb12ff863c0.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/c679b68e-025a-4c60-9c33-35258f67457a.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/c8e28577-a8b6-4dc1-9aa8-5b1ee1c7865a.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/caa42efa-e5ec-4e2f-b220-9f4605f1d2cd.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/d6776811-dc12-4407-9870-ad636722554b.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/e2d67af7-855d-4696-ac0c-3e33db5e4fdf.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/e591035c-254b-4cf3-a667-7ca2793852c4.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/eaa19cfb-488a-41fb-aba0-107c6e76b819.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/ee142dc0-aa3d-4090-ba0e-531553c7530e.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/f6492a92-f714-454c-810b-8a469b19a7bc.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/fa88943f-cb47-4117-be96-ec2c86296d82.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/fb95c039-84a9-44ff-93d4-a9efb39bd513.root',
'/store/mc/Run3Winter24Digi/DYTo2L_MLL-4to50_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v8-v2/50000/fc4202a0-8772-4349-8e86-584243b18a71.root'

'''
'/store/mc/Run3Winter24Digi/WW_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v10-v2/120000/0036882a-89fc-42f8-a0ec-8e7e99b37ff5.root',
'/store/mc/Run3Winter24Digi/WW_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v10-v2/120000/0548251d-7aa3-4a8d-ae38-2063d902b49d.root',
'/store/mc/Run3Winter24Digi/WW_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v10-v2/120000/054c836a-53e7-4764-9890-1fd41562ded4.root',
'/store/mc/Run3Winter24Digi/WW_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v10-v2/120000/055594d2-d490-4251-b779-e5e37e6dfb66.root',
'/store/mc/Run3Winter24Digi/WW_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v10-v2/120000/0564d668-53f9-4309-b10c-de08b40379b2.root',
'/store/mc/Run3Winter24Digi/WW_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v10-v2/120000/0596f188-131e-42a3-9fa7-dd96052559d9.root',
'/store/mc/Run3Winter24Digi/WW_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v10-v2/120000/05ea8c73-c5e7-4746-bc0c-8477a723b13f.root',
'/store/mc/Run3Winter24Digi/WW_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v10-v2/120000/061b1035-fc53-481a-b10f-a2df5fb3571f.root',
'/store/mc/Run3Winter24Digi/WW_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v10-v2/120000/062aba62-ebcd-44ae-8e05-d9166ee1dfe1.root',
'/store/mc/Run3Winter24Digi/WW_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v10-v2/120000/064374df-96c3-4b05-b9f9-cea8edbcb288.root',
'/store/mc/Run3Winter24Digi/WW_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v10-v2/120000/06739904-2c42-42d8-9b65-8ed5d0de88c2.root',
'/store/mc/Run3Winter24Digi/WW_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v10-v2/120000/0684e90a-479f-419c-9503-4ac42dc5b01f.root',
'/store/mc/Run3Winter24Digi/WW_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v10-v2/120000/0696042a-3a68-4d33-a71d-974da85d9d5c.root',
'/store/mc/Run3Winter24Digi/WW_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v10-v2/120000/06e21bb9-e25e-433c-a3e9-8db0ce87483a.root',
'/store/mc/Run3Winter24Digi/WW_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v10-v2/120000/078c7f3e-e485-445f-b96a-da4038cdec83.root',
'/store/mc/Run3Winter24Digi/WW_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v10-v2/120000/08b4a05d-81cb-401c-b7cc-4afe13104f25.root',
'/store/mc/Run3Winter24Digi/WW_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v10-v2/120000/08e1a06f-7f3e-4a72-97a1-ae145affc736.root',
'/store/mc/Run3Winter24Digi/WW_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v10-v2/120000/08f9fc41-c73a-437c-8e7c-8ceeb7a10333.root',
'/store/mc/Run3Winter24Digi/WW_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v10-v2/120000/0971cf63-b2ac-4a07-b668-a88d82cd846e.root',
'/store/mc/Run3Winter24Digi/WW_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v10-v2/120000/0979e220-d325-4ccb-a407-839310ae265c.root',
'/store/mc/Run3Winter24Digi/WW_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v10-v2/120000/09b793d5-f98f-476e-bf39-cedf26470cb6.root',
'/store/mc/Run3Winter24Digi/WW_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v10-v2/120000/09b7cd6e-0934-4b0c-b83e-cf13396e1127.root',
'/store/mc/Run3Winter24Digi/WW_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v10-v2/120000/09e46f6c-a9f5-4732-bec1-71b73ff5b36b.root',
'/store/mc/Run3Winter24Digi/WW_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v10-v2/120000/09f358a5-5a35-405a-992c-3ca4cb8b78f1.root',
'/store/mc/Run3Winter24Digi/WW_TuneCP5_13p6TeV_pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v10-v2/120000/0a137576-1af2-4e10-8613-a9a5a17f2dda.root'
'''
#                                '/store/mc/Run3Winter24Digi/DYto2L-4Jets_MLL-50_TuneCP5_13p6TeV_madgraphMLM-pythia8/GEN-SIM-RAW/133X_mcRun3_2024_realistic_v10_ext2-v2/2530013/765561b1-41c7-41cc-a970-66df0c5282e8.root'

                                                          ),
                            
    secondaryFileNames = cms.untracked.vstring()

#remark: the child is /store/mc/Run3Winter24MiniAOD/DYto2L-4Jets_MLL-50_TuneCP5_13p6TeV_madgraphMLM-pythia8/MINIAODSIM/133X_mcRun3_2024_realistic_v10_ext2-v2/2530000/d0ee1a98-6650-4fa5-a9f5-349001bb03d3.root
)

process.options = cms.untracked.PSet(
    IgnoreCompletely = cms.untracked.vstring(),
    Rethrow = cms.untracked.vstring(),
    TryToContinue = cms.untracked.vstring(),
    accelerators = cms.untracked.vstring('*'),
    allowUnscheduled = cms.obsolete.untracked.bool,
    canDeleteEarly = cms.untracked.vstring(),
    deleteNonConsumedUnscheduledModules = cms.untracked.bool(True),
    dumpOptions = cms.untracked.bool(False),
    emptyRunLumiMode = cms.obsolete.untracked.string,
    eventSetup = cms.untracked.PSet(
        forceNumberOfConcurrentIOVs = cms.untracked.PSet(
            allowAnyLabel_=cms.required.untracked.uint32
        ),
        numberOfConcurrentIOVs = cms.untracked.uint32(0)
    ),
    fileMode = cms.untracked.string('FULLMERGE'),
    forceEventSetupCacheClearOnNewRun = cms.untracked.bool(False),
    holdsReferencesToDeleteEarly = cms.untracked.VPSet(),
    makeTriggerResults = cms.obsolete.untracked.bool,
    modulesToCallForTryToContinue = cms.untracked.vstring(),
    modulesToIgnoreForDeleteEarly = cms.untracked.vstring(),
    numberOfConcurrentLuminosityBlocks = cms.untracked.uint32(0),
    numberOfConcurrentRuns = cms.untracked.uint32(1),
    numberOfStreams = cms.untracked.uint32(0),
    numberOfThreads = cms.untracked.uint32(1),
    printDependencies = cms.untracked.bool(False),
    sizeOfStackForThreadsInKB = cms.optional.untracked.uint32,
    throwIfIllegalParameter = cms.untracked.bool(True),
    wantSummary = cms.untracked.bool(False)
)

# Production Info
process.configurationMetadata = cms.untracked.PSet(
    annotation = cms.untracked.string('customHLT nevts:100'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.NANOAODoutput = cms.OutputModule("NanoAODOutputModule",
    compressionAlgorithm = cms.untracked.string('LZMA'),
    compressionLevel = cms.untracked.int32(9),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('NANOAOD'),
        filterName = cms.untracked.string('')
    ),
    fileName = cms.untracked.string('file:outNANO.root'),
    outputCommands = process.NANOAODEventContent.outputCommands
)

# Additional output definition

# Other statements
from HLTrigger.Configuration.CustomConfigs import ProcessName
process = ProcessName(process)

from Configuration.AlCa.GlobalTag import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:phase1_2024_realistic', '')
#process.GlobalTag = GlobalTag(process.GlobalTag, '133X_mcRun3_2024_realistic_v10', '')
#process.GlobalTag = GlobalTag(process.GlobalTag, '140X_mcRun3_2024_realistic_v26', '')
# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.NANOAODoutput_step = cms.EndPath(process.NANOAODoutput)

process.demo = cms.EDAnalyzer('TriggerAnalyzerRAWMiniAOD',
                              UseMINIAOD = cms.bool(False)
)
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string( "out_gen.root" )
                                   )
process.demo_step = cms.EndPath(process.demo)


# Schedule definition
# process.schedule imported from cff in HLTrigger.Configuration
process.schedule.insert(0, process.raw2digi_step)
process.schedule.insert(1, process.L1Reco_step)
#process.schedule.extend([process.endjob_step,process.NANOAODoutput_step])
process.schedule.extend([process.endjob_step,process.demo_step])
from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)

# customisation of the process.

# Automatic addition of the customisation function from Configuration.DataProcessing.RecoTLR
from Configuration.DataProcessing.RecoTLR import customisePostEra_Run3 

#call to customisation function customisePostEra_Run3 imported from Configuration.DataProcessing.RecoTLR
process = customisePostEra_Run3(process)

# End of customisation functions


# Customisation from command line

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion
