# Auto generated configuration file
# using: 
# Revision: 1.19 
# Source: /local/reps/CMSSW/CMSSW/Configuration/Applications/python/ConfigBuilder.py,v 
# with command line options: HLT2 --step=HLT:TutoElePhotonWPTight --era=Run3 --data --conditions auto:run3_hlt_GRun --filein /store/data/Run2023D/EGamma0/MINIAOD/PromptReco-v1/000/370/293/00000/4ff34f8d-89b6-45fd-b95f-10872b116267.root --secondfilein /store/data/Run2023D/EGamma0/RAW/v1/000/370/293/00000/25055129-76e0-4caa-8b2b-5519c6d4fef5.root,/store/data/Run2023D/EGamma0/RAW/v1/000/370/293/00000/413c0580-4451-44f9-851c-bdc13cd82e98.root,/store/data/Run2023D/EGamma0/RAW/v1/000/370/293/00000/719f3b70-3778-425e-b551-0b8a59f5afda.root,/store/data/Run2023D/EGamma0/RAW/v1/000/370/293/00000/75d4622d-e1b6-42eb-bc21-46a96324ad4b.root,/store/data/Run2023D/EGamma0/RAW/v1/000/370/293/00000/c1f4197f-c400-48d3-905c-31133b199edc.root,/store/data/Run2023D/EGamma0/RAW/v1/000/370/293/00000/c2f6f27b-0de9-40ec-91e8-e56b07f0df4c.root,/store/data/Run2023D/EGamma0/RAW/v1/000/370/293/00000/e284248b-86c4-4062-a63f-3181bbe8e61f.root,/store/data/Run2023D/EGamma0/RAW/v1/000/370/293/00000/e8163311-38ee-4ee4-a63b-5483a0ec32b6.root,/store/data/Run2023D/EGamma0/RAW/v1/000/370/293/00000/f7f33c64-3d33-45fb-abb8-1d20f1520f89.root --processName=HLT2 -n 100 --no_exec --python_filename rerunHLTandAnalyzer.py
import FWCore.ParameterSet.Config as cms

from Configuration.Eras.Era_Run3_cff import Run3

process = cms.Process('HLT2',Run3)

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('Configuration.StandardSequences.GeometryRecoDB_cff')
process.load('Configuration.StandardSequences.MagneticField_cff')
process.load('HLTrigger.Configuration.HLT_TutoElePhotonWPTight_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1000),
    output = cms.optional.untracked.allowed(cms.int32,cms.PSet)
)
process.MessageLogger.cerr.FwkReport.reportEvery = 100
# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('/store/data/Run2023D/EGamma0/MINIAOD/PromptReco-v1/000/370/293/00000/4ff34f8d-89b6-45fd-b95f-10872b116267.root'),
    secondaryFileNames = cms.untracked.vstring(
        '/store/data/Run2023D/EGamma0/RAW/v1/000/370/293/00000/25055129-76e0-4caa-8b2b-5519c6d4fef5.root',
        '/store/data/Run2023D/EGamma0/RAW/v1/000/370/293/00000/413c0580-4451-44f9-851c-bdc13cd82e98.root',
        '/store/data/Run2023D/EGamma0/RAW/v1/000/370/293/00000/719f3b70-3778-425e-b551-0b8a59f5afda.root',
        '/store/data/Run2023D/EGamma0/RAW/v1/000/370/293/00000/75d4622d-e1b6-42eb-bc21-46a96324ad4b.root',
        '/store/data/Run2023D/EGamma0/RAW/v1/000/370/293/00000/c1f4197f-c400-48d3-905c-31133b199edc.root',
        '/store/data/Run2023D/EGamma0/RAW/v1/000/370/293/00000/c2f6f27b-0de9-40ec-91e8-e56b07f0df4c.root',
        '/store/data/Run2023D/EGamma0/RAW/v1/000/370/293/00000/e284248b-86c4-4062-a63f-3181bbe8e61f.root',
        '/store/data/Run2023D/EGamma0/RAW/v1/000/370/293/00000/e8163311-38ee-4ee4-a63b-5483a0ec32b6.root',
        '/store/data/Run2023D/EGamma0/RAW/v1/000/370/293/00000/f7f33c64-3d33-45fb-abb8-1d20f1520f89.root'
    )
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
    annotation = cms.untracked.string('HLT2 nevts:100'),
    name = cms.untracked.string('Applications'),
    version = cms.untracked.string('$Revision: 1.19 $')
)

# Output definition

process.RECOSIMoutput = cms.OutputModule("PoolOutputModule",
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string(''),
        filterName = cms.untracked.string('')
    ),
    fileName = cms.untracked.string('HLT2_HLT.root'),
    outputCommands = process.RECOSIMEventContent.outputCommands,
    splitLevel = cms.untracked.int32(0)
)

# Additional output definition

# Other statements
from HLTrigger.Configuration.CustomConfigs import ProcessName
process = ProcessName(process)

from Configuration.AlCa.GlobalTag import GlobalTag
#process.GlobalTag = GlobalTag(process.GlobalTag, 'auto:run3_hlt_GRun', '')
process.GlobalTag = GlobalTag(process.GlobalTag, '140X_dataRun3_HLT_for2024TSGStudies_v1', '')

# Path and EndPath definitions
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RECOSIMoutput_step = cms.EndPath(process.RECOSIMoutput)

process.demo = cms.EDAnalyzer('TriggerAnalyzerRAWMiniAOD',
                               UseMINIAOD = cms.bool(True))
process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string( "out.root" )
                                   )
process.demo_step = cms.EndPath(process.demo)

# Schedule definition
# process.schedule imported from cff in HLTrigger.Configuration
#process.schedule.extend([process.endjob_step,process.RECOSIMoutput_step])
process.schedule.extend([process.endjob_step, process.demo_step])

from PhysicsTools.PatAlgos.tools.helpers import associatePatAlgosToolsTask
associatePatAlgosToolsTask(process)



# Customisation from command line

# Add early deletion of temporary data products to reduce peak memory need
from Configuration.StandardSequences.earlyDeleteSettings_cff import customiseEarlyDelete
process = customiseEarlyDelete(process)
# End adding early deletion
