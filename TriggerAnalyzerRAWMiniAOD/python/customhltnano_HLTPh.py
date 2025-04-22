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
#                                'file:HLTPhysics2024G_385094.root',
#                                '/store/data/Run2024I/HLTPhysics/RAW/v1/000/386/924/00000/bc217bd7-a304-442e-928b-5702bc41dc2f.root',
                                'file:/pnfs/iihe/cms/ph/sc4/store/data/Run2024I/HLTPhysics/RAW/v1/000/386/924/00000/bc217bd7-a304-442e-928b-5702bc41dc2f.root',
                                'file:/pnfs/iihe/cms/ph/sc4/store/data/Run2024I/HLTPhysics/RAW/v1/000/386/924/00000/85ac605d-ca79-4994-8734-c74661bdc9f7.root',
                                'file:/pnfs/iihe/cms/ph/sc4/store/data/Run2024I/HLTPhysics/RAW/v1/000/386/924/00000/7792bbb2-87da-4230-90c6-33f1d0f1b8be.root',
                                'file:/pnfs/iihe/cms/ph/sc4/store/data/Run2024I/HLTPhysics/RAW/v1/000/386/924/00000/46554c94-a6d0-4760-b945-afb30acd0b8d.root',
                                'file:/pnfs/iihe/cms/ph/sc4/store/data/Run2024I/HLTPhysics/RAW/v1/000/386/924/00000/0cc54b7b-9472-47c1-a060-9a91e01281d0.root',
                                'file:/pnfs/iihe/cms/ph/sc4/store/data/Run2024I/HLTPhysics/RAW/v1/000/386/924/00000/12e8c122-6559-453a-b213-2390e2d882e2.root',
                                'file:/pnfs/iihe/cms/ph/sc4/store/data/Run2024I/HLTPhysics/RAW/v1/000/386/924/00000/3d49c9b9-06bb-4dd2-8d09-eb8bd499eee1.root',
                                'file:/pnfs/iihe/cms/ph/sc4/store/data/Run2024I/HLTPhysics/RAW/v1/000/386/924/00000/40a35add-1873-4a2a-904a-b91e6267df36.root',
                                'file:/pnfs/iihe/cms/ph/sc4/store/data/Run2024I/HLTPhysics/RAW/v1/000/386/924/00000/d4667658-c6e0-4399-9612-c175b622f4cc.root',
                                'file:/pnfs/iihe/cms/ph/sc4/store/data/Run2024I/HLTPhysics/RAW/v1/000/386/924/00000/82bc12b9-c739-4000-a00d-2d0848c6ae3f.root',
                                'file:/pnfs/iihe/cms/ph/sc4/store/data/Run2024I/HLTPhysics/RAW/v1/000/386/924/00000/fbb0df90-3e9e-4c5a-99e3-50ef6e361f6c.root',
                                'file:/pnfs/iihe/cms/ph/sc4/store/data/Run2024I/HLTPhysics/RAW/v1/000/386/924/00000/c9de21f7-780e-461d-87fb-ab3382b5834a.root'
                                                          ),

    secondaryFileNames = cms.untracked.vstring()
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
process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run3_data_prompt', '')

# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.NANOAODoutput_step = cms.EndPath(process.NANOAODoutput)

process.demo = cms.EDAnalyzer('TriggerAnalyzerRAWMiniAOD',
                              UseMINIAOD = cms.bool(False)
)
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string( "out.root" )
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
