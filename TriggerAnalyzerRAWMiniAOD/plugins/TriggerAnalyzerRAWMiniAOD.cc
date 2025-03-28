// -*- C++ -*-
//
// Package:    HLTAnalysis/TriggerAnalyzerRAWMiniAOD
// Class:      TriggerAnalyzerRAWMiniAOD
// 
/**\class TriggerAnalyzerRAWMiniAOD TriggerAnalyzerRAWMiniAOD.cc HLTAnalysis/TriggerAnalyzerRAWMiniAOD/plugins/TriggerAnalyzerRAWMiniAOD.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Laurent Thomas
//         Created:  Fri, 24 Mar 2017 04:09:55 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include "DataFormats/Common/interface/AssociationMap.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/HLTReco/interface/TriggerFilterObjectWithRefs.h"
#include "DataFormats/RecoCandidate/interface/RecoEcalCandidate.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

#include "TLorentzVector.h"
#include "TTree.h"
//
// class declaration
//

// If the analyzer does not use TFileService, please remove
// the template argument to the base class so the class inherits
// from  edm::one::EDAnalyzer<> and also remove the line from
// constructor "usesResource("TFileService");"
// This will improve performance in multithreaded jobs.

class TriggerAnalyzerRAWMiniAOD : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit TriggerAnalyzerRAWMiniAOD(const edm::ParameterSet&);
      ~TriggerAnalyzerRAWMiniAOD();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  

   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

  bool PassOfflineMuonSelection(const pat::Muon *mu, reco::Vertex::Point PV);
  bool PassOfflineElectronSelection(const pat::Electron * ele, reco::Vertex::Point PV);
  bool RecoHLTMatchingORIG(const edm::Event&,double recoeta, double recophi, std::string filtername, double dRmatching = 0.3);
  bool RecoHLTMatchingHLT2(const edm::Event&,double recoeta, double recophi, std::string filtername, double dRmatching = 0.3);
  double VarStudied( const edm::Event& iEvent, double recoeta, double recophi,edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > varToken_,  edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> candToken_,   bool  dividebyE, bool dividebyEt, double dRmatching =0.3);
  vector<float> VarHLT( const edm::Event& iEvent, edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > varToken_,  edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> candToken_,   bool  dividebyE, bool dividebyEt);
      // ----------member data ---------------------------
  edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> trigobjectsMINIAODToken_;
  edm::EDGetTokenT<edm::TriggerResults> trgresultsORIGToken_;
  edm::EDGetTokenT<trigger::TriggerEvent> trigobjectsRAWToken_;
  edm::EDGetTokenT<edm::TriggerResults>  trgresultsHLT2Token_;
  edm::EDGetTokenT<std::vector<pat::Electron> > electron_token;
  edm::EDGetTokenT<std::vector<pat::Photon> > photon_token;
  edm::EDGetTokenT<std::vector<reco::Vertex> > PV_token;
  edm::EDGetTokenT<double> hltFixedGridRhoFastjetAllCaloForMuons_token;
  edm::EDGetTokenT<double> rhoJetsToken_;
  edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> photontight_l1_Filter_Token_;
  edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> photontight_et_Filter_Token_;
  edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> photontight_showershape_Filter_Token_;
  edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> photontight_hoe_Filter_Token_;
  edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> photontight_r9_Filter_Token_;
  edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> photontight_ecaliso_Filter_Token_;
  edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> photontight_hcaliso_Filter_Token_;
  edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> photontight_trackiso_Filter_Token_;
  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > >   photontight_et_Var_Token_;
  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > >   photontight_showershape_Var_Token_;
  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > >   photontight_hovere_Var_Token_;
  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > >   photontight_r9_Var_Token_;
  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > >   photontight_ecaliso_Var_Token_;
  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > >   photontight_hcaliso_Var_Token_;
  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > >   photontight_trackiso_Var_Token_;
  edm::Service<TFileService> fs;
  TTree* outputTree;
  unsigned long _eventNb;
  unsigned long _runNb;
  unsigned long _lumiBlock;
  unsigned long _bx;
  
  //Rerun HLT decisions
  bool HLT_Ele35_WPTight_Gsf;
  bool HLT_Photon50EB_TightID_TightIso;
  bool HLT_Photon14EB_Loose;
  
  //Original HLT decisions
  bool HLT_IsoMu24_ORIG;
  bool HLT_Ele32_WPTight_Gsf_ORIG;
  bool HLT_Ele35_WPTight_Gsf_ORIG;
  bool HLT_Photon50EB_TightID_TightIso_ORIG;
  bool HLT_Photon14EB_Loose_ORIG;
  bool HLT_Photon110EB_TightID_TightIso_ORIG;
  vector<float> probe_ele_pt;
  vector<float> probe_ele_eta;
  vector<float> probe_ele_phi;
  vector<float> probe_ele_mll;
  
  vector<float> probe_ele_photontight_sietaieta_HLT;
  vector<float> probe_ele_photontight_hoe_HLT;
  vector<float> probe_ele_photontight_r9_HLT;
  vector<float> probe_ele_photontight_ecaliso_HLT;
  vector<float> probe_ele_photontight_hcaliso_HLT;
  vector<float> probe_ele_photontight_trackiso_HLT;
  vector<bool> probe_ele_passphoton50cuts;
  vector<bool> probe_ele_passphoton14cuts;

  vector<float> _phEta;
  vector<float> _phPhi;
  vector<float> _phPt;
  vector<bool> _phPassTightID;
  vector<bool> _phPassLooseID;
  vector<float>_phgIso;
  vector<float>_phchIso;
  vector<float>_phnhIso;
  vector<bool> _ph_passphoton50cuts;
  vector<bool> _ph_passphoton14cuts;
  
  vector<float> hltphoton_pt;
  vector<float> hltphoton_eta;
  vector<float> hltphoton_phi;
  
  vector<float> hltphoton_photontight_sietaieta_HLT;
  vector<float> hltphoton_photontight_hoe_HLT;
  vector<float> hltphoton_photontight_r9_HLT;
  vector<float> hltphoton_photontight_ecaliso_HLT;
  vector<float> hltphoton_photontight_hcaliso_HLT;
  vector<float> hltphoton_photontight_trackiso_HLT;
  
  Float_t hlt_rho;
  Float_t rho;
  Int_t n_goodvertex;
  Int_t n_vertex;
  
  Bool_t useMINIAOD;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
TriggerAnalyzerRAWMiniAOD::TriggerAnalyzerRAWMiniAOD(const edm::ParameterSet& iConfig)
  :
  useMINIAOD(iConfig.getParameter<bool>("UseMINIAOD"))
{
  trigobjectsMINIAODToken_ = consumes<pat::TriggerObjectStandAloneCollection>( edm::InputTag("slimmedPatTrigger"));
  trigobjectsRAWToken_=consumes<trigger::TriggerEvent>(edm::InputTag("hltTriggerSummaryAOD::HLT2"));
  trgresultsORIGToken_= consumes<edm::TriggerResults>( edm::InputTag("TriggerResults::HLT") );
  trgresultsHLT2Token_= consumes<edm::TriggerResults>( edm::InputTag("TriggerResults::HLT2") );
  photontight_et_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaCandidates","","HLT2") );
  photontight_showershape_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaClusterShape","sigmaIEtaIEta5x5NoiseCleaned","HLT2") );
  photontight_hovere_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaHoverE","","HLT2") );
  photontight_r9_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaR9ID","","HLT2") );
  photontight_ecaliso_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaEcalPFClusterIso","","HLT2")  );
  photontight_hcaliso_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaHcalPFClusterIso","","HLT2")  );
  photontight_trackiso_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaHollowTrackIso","","HLT2")  ); 
  photontight_l1_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEGL1SingleEGLowFilter","","HLT2") ) ;
  photontight_et_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEG14DummyFilter","","HLT2") ) ;
  photontight_showershape_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEG14DummyClusterShapeFilter","","HLT2") );
  photontight_hoe_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEG14DummyHEFilter","","HLT2") );
  photontight_r9_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEG14DummyR9Filter","","HLT2") );
  photontight_ecaliso_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEG14DummyEcalIsoFilter","","HLT2") );
  photontight_hcaliso_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEG14DummyHcalIsoFilter","","HLT2") );
  photontight_trackiso_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEG14DummyTrackIsoFilter","","HLT2") );
  /*
  photontight_l1_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEGL1SingleIsoEG28to45Filter","","HLT2") ) ;
  photontight_et_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEG50EBTightIDTightIsoEtFilter","","HLT2") ) ;
  photontight_showershape_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEG50EBTightIDTightIsoClusterShapeFilter","","HLT2") );
  photontight_hoe_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEG50EBTightIDTightIsoHEFilter","","HLT2") );
  photontight_r9_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEG50EBTightIDTightIsoR9Filter","","HLT2") );
  photontight_ecaliso_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEG50EBTightIDTightIsotEcalIsoFilter","","HLT2") );
  photontight_hcaliso_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEG50EBTightIDTightIsoHcalIsoFilter","","HLT2") );
  photontight_trackiso_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEG50EBTightIDTightIsoTrackIsoFilter","","HLT2") );
  */
  //electron_token = consumes<std::vector<reco::Electron> >(edm::InputTag("gedGsfElectrons") );
  //photon_token = consumes<std::vector<reco::Photon> >(edm::InputTag("gedPhotons") );
  //PV_token = consumes<std::vector<reco::Vertex> > (edm::InputTag("offlinePrimaryVertices"));
  electron_token = consumes<std::vector<pat::Electron> >(edm::InputTag("slimmedElectrons") );
  photon_token = consumes<std::vector<pat::Photon> >(edm::InputTag("slimmedPhotons") );
  PV_token = consumes<std::vector<reco::Vertex> > (edm::InputTag("offlineSlimmedPrimaryVertices"));
  
  hltFixedGridRhoFastjetAllCaloForMuons_token = consumes<double>(edm::InputTag("hltFixedGridRhoFastjetAllCaloForMuons","","HLT2"));
  rhoJetsToken_ = consumes<double>(edm::InputTag("fixedGridRhoFastjetAll","",""));
    
  outputTree = fs->make<TTree>("tree","tree");
  
}


TriggerAnalyzerRAWMiniAOD::~TriggerAnalyzerRAWMiniAOD()
{
  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
}


//
// member functions
//

// ------------ method called for each event  ------------
void
TriggerAnalyzerRAWMiniAOD::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  using namespace edm;
  using namespace reco;
  using namespace std;
  _runNb = iEvent.id().run();
  _eventNb = iEvent.id().event();
  _lumiBlock = iEvent.luminosityBlock();
  _bx=iEvent.bunchCrossing();
  
  HLT_Ele35_WPTight_Gsf= false;
  HLT_Photon50EB_TightID_TightIso= false;
  HLT_Photon14EB_Loose= false;

  HLT_IsoMu24_ORIG=false;
  HLT_Ele32_WPTight_Gsf_ORIG=false;
  HLT_Ele35_WPTight_Gsf_ORIG=false;
  HLT_Photon50EB_TightID_TightIso_ORIG=false;
  HLT_Photon14EB_Loose_ORIG=false;
  HLT_Photon110EB_TightID_TightIso_ORIG=false;


  
  //Accessing trigger bits:
  //This works in both RAW, AOD or MINIAOD
  //Here we access the decision provided by the HLT (i.e. original trigger step).
  edm::Handle<edm::TriggerResults> trigResults;
  iEvent.getByToken(trgresultsORIGToken_, trigResults);
  if( !trigResults.failedToGet() ) {
    int N_Triggers = trigResults->size();
    const edm::TriggerNames & trigName = iEvent.triggerNames(*trigResults);
    
    for( int i_Trig = 0; i_Trig < N_Triggers; ++i_Trig ) {
      if (trigResults.product()->accept(i_Trig)) {
	TString TrigPath =trigName.triggerName(i_Trig);
	//      cout << "Passed path: " << TrigPath<<endl;
	if(TrigPath.Index("HLT_IsoMu24_v") >=0) HLT_IsoMu24_ORIG=true;
	if(TrigPath.Index("HLT_Ele32_WPTight_Gsf_v") >=0) HLT_Ele32_WPTight_Gsf_ORIG=true;
	if(TrigPath.Index("HLT_Ele35_WPTight_Gsf_v") >=0) HLT_Ele35_WPTight_Gsf_ORIG=true;
	if(TrigPath.Index("HLT_Photon50EB_TightID_TightIso_v") >=0)
	  {
	    HLT_Photon50EB_TightID_TightIso_ORIG=true;
	    std::cout << "HLT_Photon50EB_TightID_TightIso_ORIG Passed" << std::endl;
	  }
	if (TrigPath.Index("HLT_Photon14EB_Loose_v") >=0)
	  {
	    HLT_Photon14EB_Loose_ORIG=true;
	    std::cout << "HLT_Photon14EB_Loose_ORIG Passed" << std::endl;
	  }
	if(TrigPath.Index("HLT_Photon110EB_TightID_TightIso_v") >=0) HLT_Photon110EB_TightID_TightIso_ORIG=true;
      }
    }
  }
  
  edm::Handle<edm::TriggerResults> trigResults_HLT2;
  iEvent.getByToken(trgresultsHLT2Token_, trigResults_HLT2);
  if( !trigResults_HLT2.failedToGet() ) {
    int N_Triggers = trigResults_HLT2->size();
    const edm::TriggerNames & trigName = iEvent.triggerNames(*trigResults_HLT2);
    
    for( int i_Trig = 0; i_Trig < N_Triggers; ++i_Trig ) {
      if (trigResults_HLT2.product()->accept(i_Trig)) {
	TString TrigPath =trigName.triggerName(i_Trig);
	//      cout << "Passed path: " << TrigPath<<endl;
	if(TrigPath.Index("HLT_Ele35_WPTight_Gsf_v") >=0) HLT_Ele35_WPTight_Gsf=true;
	if(TrigPath.Index("HLT_Photon50EB_TightID_TightIso_v") >=0)
	  {
	    HLT_Photon50EB_TightID_TightIso=true;
	    std::cout << "HLT_Photon50EB_TightID_TightIso Passed" << std::endl;
	  }
	if(TrigPath.Index("HLT_Photon14EB_Loose_v") >=0)
	  {
	    HLT_Photon14EB_Loose=true;
	    std::cout << "HLT_Photon14EB_Loose Passed" << std::endl;
	  }
      }
    }
  }
  
  n_goodvertex = -1;
  n_vertex = -1;
  rho = -1;
  if(useMINIAOD){
    edm::Handle<std::vector<Vertex> > theVertices;
    iEvent.getByToken(PV_token,theVertices) ;
    
    n_vertex = theVertices->size();
    Vertex::Point PV(0,0,0);
    if( n_vertex) PV = theVertices->begin()->position();
    
    n_goodvertex = 0;
    for(unsigned int i = 0;i < theVertices->size(); i++){
      const Vertex* PVtx = &((*theVertices)[i]);
      if(PVtx->isFake())continue;
      if(PVtx->ndof()<=4)continue;
      if(PVtx->position().Rho()>2.)continue;
      if(abs(PVtx->z())>24)continue;
      
      n_goodvertex ++;
    }
    edm::Handle< std::vector<pat::Electron> > electrons;
    //edm::Handle< std::vector<reco::Electron> > electrons;
    iEvent.getByToken(electron_token,electrons );
    //First loop to find a tag electron
    for( std::vector<pat::Electron>::const_iterator tagele = (*electrons).begin(); tagele != (*electrons).end(); tagele++ ) {
      //for( std::vector<reco::Electron>::const_iterator tagele = (*electrons).begin(); tagele != (*electrons).end(); tagele++ ) {
      if(!PassOfflineElectronSelection(&*tagele,PV)) continue;
      double pttagele = tagele->pt();
      double etatagele = tagele->eta();
      double phitagele = tagele->phi();
      if(pttagele<35) continue;
      if(!RecoHLTMatchingORIG(iEvent,etatagele,phitagele,"hltEle35noerWPTightGsfTrackIsoFilter") ) continue;
      //Second loop on the probe
      for( std::vector<pat::Electron>::const_iterator probeele = (*electrons).begin(); probeele != (*electrons).end(); probeele++ ) {
	//for( std::vector<reco::Electron>::const_iterator probeele = (*electrons).begin(); probeele != (*electrons).end(); probeele++ ) {
	if(tagele==probeele)continue;//Tag and Probe should be different (obviously)

	if(!PassOfflineElectronSelection(&*probeele,PV)) continue;
	double ptprobeele = probeele->pt();
	double etaprobeele = probeele->eta();
	double phiprobeele = probeele->phi();
	
	TLorentzVector p4tag, p4probe;
	p4tag.SetPtEtaPhiM(pttagele,etatagele,phitagele,0);
	p4probe.SetPtEtaPhiM(ptprobeele,etaprobeele,phiprobeele,0);
	double mass = (p4tag+p4probe).Mag();

	if(mass<60 ||mass>120) continue;
	if(tagele->charge() * probeele->charge()>0)continue;

	bool  dividebyE = false; bool dividebyEt = false;

	double photontight_sietaieta_HLT = VarStudied(iEvent, etaprobeele,phiprobeele,photontight_showershape_Var_Token_,photontight_et_Filter_Token_ ,dividebyE, dividebyEt);
	dividebyE = true; dividebyEt = false;
	double photontight_hoe_HLT  = VarStudied(iEvent, etaprobeele,phiprobeele,photontight_hovere_Var_Token_,photontight_showershape_Filter_Token_ ,dividebyE, dividebyEt);
	dividebyE = false;  dividebyEt = false;
	double photontight_r9_HLT  = VarStudied(iEvent, etaprobeele,phiprobeele,photontight_r9_Var_Token_,photontight_hoe_Filter_Token_ ,dividebyE, dividebyEt);
	dividebyE =false; dividebyEt = true;
	double photontight_ecaliso_HLT  = VarStudied(iEvent, etaprobeele,phiprobeele,photontight_ecaliso_Var_Token_,photontight_r9_Filter_Token_ ,dividebyE, dividebyEt);
	double photontight_hcaliso_HLT  = VarStudied(iEvent, etaprobeele,phiprobeele,photontight_hcaliso_Var_Token_,photontight_ecaliso_Filter_Token_ ,dividebyE, dividebyEt);
	double photontight_trackiso_HLT  = VarStudied(iEvent, etaprobeele,phiprobeele,photontight_trackiso_Var_Token_,photontight_hcaliso_Filter_Token_ ,dividebyE, dividebyEt);

	
	probe_ele_pt.push_back(ptprobeele);
	probe_ele_eta.push_back(etaprobeele);
	probe_ele_phi.push_back(phiprobeele);
	probe_ele_mll.push_back(mass);

	probe_ele_photontight_sietaieta_HLT.push_back(photontight_sietaieta_HLT);
	probe_ele_photontight_hoe_HLT.push_back(photontight_hoe_HLT);
	probe_ele_photontight_r9_HLT.push_back(photontight_r9_HLT);
	probe_ele_photontight_ecaliso_HLT.push_back(photontight_ecaliso_HLT);
	probe_ele_photontight_hcaliso_HLT.push_back(photontight_hcaliso_HLT);
	probe_ele_photontight_trackiso_HLT.push_back(photontight_trackiso_HLT);
	probe_ele_passphoton50cuts.push_back(RecoHLTMatchingHLT2(iEvent,etaprobeele,phiprobeele,"hltEG50EBTightIDTightIsoTrackIsoFilter") );
	probe_ele_passphoton14cuts.push_back(RecoHLTMatchingHLT2(iEvent,etaprobeele,phiprobeele,"hltEG14DummyTrackIsoFilter") );
	
      }
    }

    edm::Handle<double> rhoJets;
    iEvent.getByToken(rhoJetsToken_,rhoJets);
    rho = *rhoJets;
    
    edm::Handle< std::vector<pat::Photon> > photons;
    //edm::Handle< std::vector<reco::Photon> > photons;
    iEvent.getByToken(photon_token,photons );
    for( std::vector<pat::Photon>::const_iterator ph = (*photons).begin(); ph != (*photons).end(); ph++ ) {
      //for( std::vector<reco::Photon>::const_iterator ph = (*photons).begin(); ph != (*photons).end(); ph++ ) {
      if((&*ph)->pt()<35)continue;
      bool passtightid = (&*ph)->photonID("mvaPhoID-RunIIFall17-v2-wp80");
      bool passlooseid = (&*ph)->photonID("mvaPhoID-RunIIFall17-v2-wp90");
      
      _phEta.push_back((&*ph)->eta());
      _phPhi.push_back((&*ph)->phi());
      _phPt.push_back( (&*ph)->pt());
      _phPassTightID.push_back(passtightid);
      _phPassLooseID.push_back(passlooseid);
      
      double chIso = (&*ph)->chargedHadronIso();
      double nhIso = (&*ph)->neutralHadronIso();
      double gIso = (&*ph)->photonIso();
      
      _phgIso.push_back(gIso);
      _phchIso.push_back(chIso);
      _phnhIso.push_back(nhIso);
      _ph_passphoton50cuts.push_back(RecoHLTMatchingHLT2(iEvent,(&*ph)->eta(),(&*ph)->phi(),"hltEG50EBTightIDTightIsoTrackIsoFilter") );
      _ph_passphoton14cuts.push_back(RecoHLTMatchingHLT2(iEvent,(&*ph)->eta(),(&*ph)->phi(),"hltEG14DummyTrackIsoFilter") );
      
    }
  }
  
  
  
  
  edm::Handle<double> hltrhoJets;
  iEvent.getByToken(hltFixedGridRhoFastjetAllCaloForMuons_token,hltrhoJets);
  if(hltrhoJets.isValid()  ){
    hlt_rho = *hltrhoJets;
  }
  else hlt_rho = -1;
  
  
  edm::Handle<trigger::TriggerFilterObjectWithRefs> PrevFilterOutput;
  iEvent.getByToken (photontight_l1_Filter_Token_, PrevFilterOutput);
  
  std::vector<edm::Ref<std::vector<reco::RecoEcalCandidate> > > recoCands;
  
  if(PrevFilterOutput.isValid()  ){
    std::cout << "# ----------------------------------------------" << std::endl;
    std::cout << "# [0] PrevFilterOutput Valid!" << std::endl;
    std::cout << "# ----------------------------------------------" << std::endl;

    PrevFilterOutput->getObjects(trigger::TriggerCluster, recoCands);
    if(recoCands.empty())PrevFilterOutput->getObjects(trigger::TriggerPhoton, recoCands);
    for (unsigned int i=0; i<recoCands.size(); i++) {
      edm::Ref<std::vector<reco::RecoEcalCandidate> > ref = recoCands[i];
      
      float energy = ref->superCluster()->energy();
      float ptphoton = ref->superCluster()->energy() * sin (2*atan(exp(-ref->eta())));
      double etaphoton = ref->eta();
      double phiphoton = ref->phi();
      
      bool dividebyE = false; bool dividebyEt = false;
      double photontight_sietaieta_HLT = VarStudied(iEvent, etaphoton,phiphoton,photontight_showershape_Var_Token_,photontight_et_Filter_Token_ ,dividebyE, dividebyEt);
      dividebyE = true; dividebyEt = false;
      double photontight_hoe_HLT  = VarStudied(iEvent, etaphoton,phiphoton,photontight_hovere_Var_Token_,photontight_showershape_Filter_Token_ ,dividebyE, dividebyEt);
      dividebyE = false;  dividebyEt = false;
      double photontight_r9_HLT  = VarStudied(iEvent, etaphoton,phiphoton,photontight_r9_Var_Token_,photontight_hoe_Filter_Token_ ,dividebyE, dividebyEt);
      dividebyE =false; dividebyEt = true;
      double photontight_ecaliso_HLT  = VarStudied(iEvent, etaphoton,phiphoton,photontight_ecaliso_Var_Token_,photontight_r9_Filter_Token_ ,dividebyE, dividebyEt);
      double photontight_hcaliso_HLT  = VarStudied(iEvent, etaphoton,phiphoton,photontight_hcaliso_Var_Token_,photontight_ecaliso_Filter_Token_ ,dividebyE, dividebyEt);
      double photontight_trackiso_HLT  = VarStudied(iEvent, etaphoton,phiphoton,photontight_trackiso_Var_Token_,photontight_hcaliso_Filter_Token_ ,dividebyE, dividebyEt);
      
      hltphoton_pt.push_back(ptphoton);
      hltphoton_eta.push_back(etaphoton);
      hltphoton_phi.push_back(phiphoton);
      
      hltphoton_photontight_sietaieta_HLT.push_back(photontight_sietaieta_HLT);
      hltphoton_photontight_hoe_HLT.push_back(photontight_hoe_HLT);
      hltphoton_photontight_r9_HLT.push_back(photontight_r9_HLT);
      hltphoton_photontight_ecaliso_HLT.push_back(photontight_ecaliso_HLT);
      hltphoton_photontight_hcaliso_HLT.push_back(photontight_hcaliso_HLT);
      hltphoton_photontight_trackiso_HLT.push_back(photontight_trackiso_HLT);
      
    }
  }
  
  outputTree->Fill();
  
  probe_ele_pt.clear();
  probe_ele_eta.clear();
  probe_ele_phi.clear();
  probe_ele_mll.clear();
  probe_ele_photontight_sietaieta_HLT.clear();
  probe_ele_photontight_hoe_HLT.clear();
  probe_ele_photontight_r9_HLT.clear();
  probe_ele_photontight_ecaliso_HLT.clear();
  probe_ele_photontight_hcaliso_HLT.clear();
  probe_ele_photontight_trackiso_HLT.clear();
  probe_ele_passphoton50cuts.clear();
  probe_ele_passphoton14cuts.clear();
  
  hltphoton_pt.clear();
  hltphoton_eta.clear();
  hltphoton_phi.clear();
  hltphoton_photontight_sietaieta_HLT.clear();
  hltphoton_photontight_hoe_HLT.clear();
  hltphoton_photontight_r9_HLT.clear();
  hltphoton_photontight_ecaliso_HLT.clear();
  hltphoton_photontight_hcaliso_HLT.clear();
  hltphoton_photontight_trackiso_HLT.clear();
  
  
  _phEta.clear();
  _phPhi.clear();
  _phPt.clear();
  _phPassTightID.clear();
  _phPassLooseID.clear();
  _phgIso.clear();
  _phchIso.clear();
  _phnhIso.clear();
  
  _ph_passphoton50cuts.clear();
  _ph_passphoton14cuts.clear();
  
}


// ------------ method called once each job just before starting event loop  ------------
void 
TriggerAnalyzerRAWMiniAOD::beginJob()
{
  outputTree->Branch("_eventNb",   &_eventNb,   "_eventNb/l");
  outputTree->Branch("_runNb",     &_runNb,     "_runNb/l");
  outputTree->Branch("_lumiBlock", &_lumiBlock, "_lumiBlock/l");
  outputTree->Branch("_bx", &_bx, "_bx/l");
  outputTree->Branch("rho",&rho,"rho/F");
  outputTree->Branch("hlt_rho",&hlt_rho,"hlt_rho/F");
  outputTree->Branch("n_goodvertex",&n_goodvertex,"n_goodvertex/I");
  outputTree->Branch("n_vertex",&n_vertex,"n_vertex/I");
  outputTree->Branch("HLT_Ele35_WPTight_Gsf",&HLT_Ele35_WPTight_Gsf,"HLT_Ele35_WPTight_Gsf/O");
  outputTree->Branch("HLT_Photon50EB_TightID_TightIso",&HLT_Photon50EB_TightID_TightIso,"HLT_Photon50EB_TightID_TightIso/O");
  outputTree->Branch("HLT_Photon14EB_Loose",&HLT_Photon14EB_Loose,"HLT_Photon14EB_Loose/O");
  
  outputTree->Branch("HLT_Ele32_WPTight_Gsf_ORIG",&HLT_Ele32_WPTight_Gsf_ORIG,"HLT_Ele32_WPTight_Gsf_ORIG/O");
  outputTree->Branch("HLT_Ele35_WPTight_Gsf_ORIG",&HLT_Ele35_WPTight_Gsf_ORIG,"HLT_Ele35_WPTight_Gsf_ORIG/O");
  outputTree->Branch("HLT_IsoMu24_ORIG",&HLT_IsoMu24_ORIG,"HLT_IsoMu24_ORIG/O");
  outputTree->Branch("HLT_Photon50EB_TightID_TightIso_ORIG",&HLT_Photon50EB_TightID_TightIso_ORIG,"HLT_Photon50EB_TightID_TightIso_ORIG/O");
  outputTree->Branch("HLT_Photon14EB_Loose_ORIG",&HLT_Photon14EB_Loose_ORIG,"HLT_Photon14EB_Loose_ORIG/O");
  outputTree->Branch("HLT_Photon110EB_TightID_TightIso_ORIG",&HLT_Photon110EB_TightID_TightIso_ORIG,"HLT_Photon110EB_TightID_TightIso_ORIG/O");
  
  outputTree->Branch("probe_ele_pt",&probe_ele_pt);
  outputTree->Branch("probe_ele_eta",&probe_ele_eta);
  outputTree->Branch("probe_ele_phi",&probe_ele_phi);
  outputTree->Branch("probe_ele_mll",&probe_ele_mll);
  outputTree->Branch("probe_ele_photontight_sietaieta_HLT",&probe_ele_photontight_sietaieta_HLT);
  outputTree->Branch("probe_ele_photontight_hoe_HLT",&probe_ele_photontight_hoe_HLT);
  outputTree->Branch("probe_ele_photontight_r9_HLT",&probe_ele_photontight_r9_HLT);
  outputTree->Branch("probe_ele_photontight_ecaliso_HLT",&probe_ele_photontight_ecaliso_HLT);
  outputTree->Branch("probe_ele_photontight_hcaliso_HLT",&probe_ele_photontight_hcaliso_HLT);
  outputTree->Branch("probe_ele_photontight_trackiso_HLT",&probe_ele_photontight_trackiso_HLT);
  outputTree->Branch("probe_ele_passphoton50cuts",&probe_ele_passphoton50cuts);
  outputTree->Branch("probe_ele_passphoton14cuts",&probe_ele_passphoton14cuts);
  outputTree->Branch("hltphoton_pt",&hltphoton_pt);
  outputTree->Branch("hltphoton_eta",&hltphoton_eta);
  outputTree->Branch("hltphoton_phi",&hltphoton_phi);
  outputTree->Branch("hltphoton_photontight_sietaieta_HLT",&hltphoton_photontight_sietaieta_HLT);
  outputTree->Branch("hltphoton_photontight_hoe_HLT",&hltphoton_photontight_hoe_HLT);
  outputTree->Branch("hltphoton_photontight_r9_HLT",&hltphoton_photontight_r9_HLT);
  outputTree->Branch("hltphoton_photontight_ecaliso_HLT",&hltphoton_photontight_ecaliso_HLT);
  outputTree->Branch("hltphoton_photontight_hcaliso_HLT",&hltphoton_photontight_hcaliso_HLT);
  outputTree->Branch("hltphoton_photontight_trackiso_HLT",&hltphoton_photontight_trackiso_HLT);
  outputTree->Branch("_phEta",&_phEta);
  outputTree->Branch("_phPhi",&_phPhi);
  outputTree->Branch("_phPt",&_phPt);
  outputTree->Branch("_phPassTightID",&_phPassTightID);
  outputTree->Branch("_phPassLooseID",&_phPassLooseID);
  outputTree->Branch("_phgIso",&_phgIso);
  outputTree->Branch("_phchIso",&_phchIso);
  outputTree->Branch("_phnhIso",&_phnhIso);
  outputTree->Branch("_ph_passphoton50cuts",&_ph_passphoton50cuts);
  outputTree->Branch("_ph_passphoton14cuts",&_ph_passphoton14cuts);
  
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TriggerAnalyzerRAWMiniAOD::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
TriggerAnalyzerRAWMiniAOD::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}




bool TriggerAnalyzerRAWMiniAOD::PassOfflineElectronSelection(const pat::Electron * ele, reco::Vertex::Point PV){
  //bool TriggerAnalyzerRAWMiniAOD::PassOfflineElectronSelection(const reco::Electron * ele, reco::Vertex::Point PV){
  const reco::GsfTrackRef gsfTrack = ele->gsfTrack();
  if (!gsfTrack.isNonnull()) return false;
  if( TMath::Abs(gsfTrack->dxy(PV)) > 0.05  )  return false;
  if( TMath::Abs(gsfTrack->dz(PV)) > 0.2  )  return false;
  if(TMath::Abs(ele->superCluster()->eta()) >2.5) return false;
  else if( TMath::Abs(ele->superCluster()->eta()) < 1.479  ) {
    if( TMath::Abs(ele->full5x5_sigmaIetaIeta()) > 0.0103 ) return  false;
    if( TMath::Abs(ele->deltaEtaSuperClusterTrackAtVtx()) > 0.0105 ) return  false;
    if( TMath::Abs(ele->deltaPhiSuperClusterTrackAtVtx()) > 0.115  ) return  false;
    if( TMath::Abs(ele->hadronicOverEm())  > 0.104  ) return  false;
    if( TMath::Abs(1.0/ele->ecalEnergy() - ele->eSuperClusterOverP()/ele->ecalEnergy() )>0.102 ) return  false;
    if( TMath::Abs(gsfTrack->dxy(PV)) > 0.0261) return false;
    if( TMath::Abs(gsfTrack->dz(PV)) > 0.41) return false;
    if(gsfTrack->hitPattern().numberOfLostHits(reco::HitPattern::MISSING_INNER_HITS)>2) return  false;
  }
  else {
    if( TMath::Abs(ele->full5x5_sigmaIetaIeta()) > 0.0301 ) return  false;
    if( TMath::Abs(ele->deltaEtaSuperClusterTrackAtVtx()) > 0.00814 ) return  false;
    if( TMath::Abs(ele->deltaPhiSuperClusterTrackAtVtx()) > 0.182  ) return  false;
    if( TMath::Abs(ele->hadronicOverEm())  > 0.0897  ) return  false;
    if( TMath::Abs(1.0/ele->ecalEnergy() - ele->eSuperClusterOverP()/ele->ecalEnergy() )>0.126 ) return  false;
    if( TMath::Abs(gsfTrack->dxy(PV)) > 0.0118) return false;
    if( TMath::Abs(gsfTrack->dz(PV)) > 0.822) return false;
    if(gsfTrack->hitPattern().numberOfLostHits(reco::HitPattern::MISSING_INNER_HITS)>1) return  false;
    
    
  }
  
  double iso = (ele->pfIsolationVariables().sumChargedHadronPt 
		+ TMath::Max(0.0, ele->pfIsolationVariables().sumNeutralHadronEt + ele->pfIsolationVariables().sumPhotonEt - 0.5*ele->pfIsolationVariables().sumPUPt ) 
		) /ele->pt() ; 
  if(iso>0.2) return false; 
  return true;
  
}

bool TriggerAnalyzerRAWMiniAOD::RecoHLTMatchingORIG(const edm::Event& iEvent, double recoeta, double recophi, std::string filtername, double dRmatching){
  edm::Handle<edm::TriggerResults> trigResults;
  iEvent.getByToken(trgresultsORIGToken_, trigResults);
  
  edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects;
  iEvent.getByToken(trigobjectsMINIAODToken_, triggerObjects);
  
  const edm::TriggerNames &names = iEvent.triggerNames(*trigResults);
  for (pat::TriggerObjectStandAlone obj : *triggerObjects) {
    obj.unpackFilterLabels(iEvent,*trigResults);
    obj.unpackPathNames(names);
    for (unsigned h = 0; h < obj.filterLabels().size(); ++h){
      std::string myfillabl=obj.filterLabels()[h];
      if( myfillabl.find(filtername)!=std::string::npos   && deltaR(recoeta,recophi, obj.eta(),obj.phi())<dRmatching ) return true;
    }
  }
  
  return false;
}


bool TriggerAnalyzerRAWMiniAOD::RecoHLTMatchingHLT2(const edm::Event& iEvent, double recoeta, double recophi, std::string filtername, double dRmatching){
  edm::Handle<edm::TriggerResults> trigResults;
  iEvent.getByToken(trgresultsHLT2Token_, trigResults);
  edm::Handle<trigger::TriggerEvent> triggerObjectsSummary;
  iEvent.getByToken(trigobjectsRAWToken_ ,triggerObjectsSummary);
  trigger::TriggerObjectCollection selectedObjects;
  if (triggerObjectsSummary.isValid()) {
    size_t filterIndex = (*triggerObjectsSummary).filterIndex( edm::InputTag(filtername,"","HLT2") );
    trigger::TriggerObjectCollection allTriggerObjects = triggerObjectsSummary->getObjects();
    if (filterIndex < (*triggerObjectsSummary).sizeFilters()) {
      const trigger::Keys &keys = (*triggerObjectsSummary).filterKeys(filterIndex);
      for (size_t j = 0; j < keys.size(); j++) {
        trigger::TriggerObject foundObject = (allTriggerObjects)[keys[j]];
	//cout <<"object found, printing pt, eta, phi: " <<foundObject.pt()<<", "<<foundObject.eta()<<", "<< foundObject.phi() <<endl;
	if(deltaR(recoeta,recophi, foundObject.eta(), foundObject.phi())<dRmatching ) return true;
	
      }
    }
  }
  
  return false;
}

double TriggerAnalyzerRAWMiniAOD::VarStudied( const edm::Event& iEvent, double recoeta, double recophi,
                                              edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > varToken_,  edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> candToken_,   bool  dividebyE, bool dividebyEt, double dRmatching ){
  
  double thevar = -1.;
  
  //Inspired from http://cmslxr.fnal.gov/source/HLTrigger/Egamma/src/HLTGenericFilter.cc
  edm::Handle<trigger::TriggerFilterObjectWithRefs> PrevFilterOutput;
  iEvent.getByToken (candToken_, PrevFilterOutput);
  
  edm::Handle<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > depMap;
  iEvent.getByToken (varToken_,depMap);
  
  std::vector<edm::Ref<std::vector<reco::RecoEcalCandidate> > > recoCands;

  if(PrevFilterOutput.isValid()&&  depMap.isValid() ){
    std::cout << "# ----------------------------------------------" << std::endl;
    std::cout << "# [1] PrevFilterOutput Valid!" << std::endl;
    std::cout << "# ----------------------------------------------" << std::endl;
    PrevFilterOutput->getObjects(trigger::TriggerCluster, recoCands);
    if(recoCands.empty())PrevFilterOutput->getObjects(trigger::TriggerPhoton, recoCands);
    
    double dRmin = dRmatching;
    for (unsigned int i=0; i<recoCands.size(); i++) {
      edm::Ref<std::vector<reco::RecoEcalCandidate> > ref = recoCands[i];
      typename edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > >::const_iterator mapi = (*depMap).find( ref );
      float vali = mapi->val;
      float EtaSC = ref->eta();
      float PhiSC = ref->phi();
      
      if(deltaR(recoeta,recophi,EtaSC,PhiSC ) > dRmin )continue;
      dRmin = deltaR(recoeta,recophi,EtaSC,PhiSC ) ;
      float energy = ref->superCluster()->energy();
      float et = ref->superCluster()->energy() * sin (2*atan(exp(-ref->eta())));
      thevar = (double) vali;
      if(dividebyE)thevar = (double)vali/energy;
      if(dividebyEt)thevar =(double) vali/et;
      
    }
  }
  return thevar;
}

vector<float> TriggerAnalyzerRAWMiniAOD::VarHLT( const edm::Event& iEvent, edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > varToken_,  edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> candToken_,   bool  dividebyE, bool dividebyEt){
  vector <float > result ;
  double thevar = 0.;
  
  //Inspired from http://cmslxr.fnal.gov/source/HLTrigger/Egamma/src/HLTGenericFilter.cc
  edm::Handle<trigger::TriggerFilterObjectWithRefs> PrevFilterOutput;
  iEvent.getByToken (candToken_, PrevFilterOutput);
  
  edm::Handle<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > depMap;
  iEvent.getByToken (varToken_,depMap);
  
  std::vector<edm::Ref<std::vector<reco::RecoEcalCandidate> > > recoCands;
  
  
  if(PrevFilterOutput.isValid()&&  depMap.isValid() ){
    std::cout << "# ----------------------------------------------" << std::endl;
    std::cout << "# [2] PrevFilterOutput Valid!" << std::endl;
    std::cout << "# ----------------------------------------------" << std::endl;

    PrevFilterOutput->getObjects(trigger::TriggerCluster, recoCands);
    if(recoCands.empty())PrevFilterOutput->getObjects(trigger::TriggerPhoton, recoCands);
    
    
    for (unsigned int i=0; i<recoCands.size(); i++) {
      edm::Ref<std::vector<reco::RecoEcalCandidate> > ref = recoCands[i];
      typename edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > >::const_iterator mapi = (*depMap).find( ref );
      float vali = mapi->val;
      
      float energy = ref->superCluster()->energy();
      float et = ref->superCluster()->energy() * sin (2*atan(exp(-ref->eta())));
      thevar = (double) vali;
      if(dividebyE)thevar = (double)vali/energy;
      if(dividebyEt)thevar =(double) vali/et;
      
      result.push_back(thevar);
    }
  }
  
  return result;
}


//define this as a plug-in
DEFINE_FWK_MODULE(TriggerAnalyzerRAWMiniAOD);
