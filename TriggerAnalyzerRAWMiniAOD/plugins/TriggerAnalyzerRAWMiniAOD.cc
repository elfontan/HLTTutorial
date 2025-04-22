//Todo: add pfclusterecalisodr0p2 (already in the ele32 relax sequence)
//Also add gsf pt eta phi charge to probe ele (only done for hltphoton)

//Add HLTEle23Ele12 and DoubleEle25
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
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/EgammaReco/interface/ElectronSeed.h"
#include "DataFormats/HLTReco/interface/TriggerFilterObjectWithRefs.h"
#include "DataFormats/EgammaReco/interface/SuperClusterFwd.h"
#include "SimDataFormats/GeneratorProducts/interface/LHEEventProduct.h"
#include "SimDataFormats/GeneratorProducts/interface/LHERunInfoProduct.h"

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
  double VarStudied( const edm::Event& iEvent, double recoeta, double recophi,edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > varToken_,  edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> candToken_,   bool  dividebyE, bool dividebyEt, double dRmatching =0.3, bool iset=false);
  vector<float> VarHLT( const edm::Event& iEvent, edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > varToken_,  edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> candToken_,   bool  dividebyE, bool dividebyEt);

  float calDPhi1Sq(reco::ElectronSeedCollection::const_iterator seed, int charge) const;
  float calDPhi2Sq(reco::ElectronSeedCollection::const_iterator seed, int charge) const;
  float calDZ2Sq(reco::ElectronSeedCollection::const_iterator seed, int charge) const;
  double PixelMatchVariable( const edm::Event& iEvent, double recoeta, double recophi, edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> candToken_,   double dRmatching=0.3 );
      // ----------member data ---------------------------


  edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> trigobjectsMINIAODToken_;
  edm::EDGetTokenT<edm::TriggerResults> trgresultsORIGToken_;
  edm::EDGetTokenT<trigger::TriggerEvent> trigobjectsRAWORIGToken_;
  edm::EDGetTokenT<trigger::TriggerEvent> trigobjectsRAWHLT2Token_;
  edm::EDGetTokenT<edm::TriggerResults>  trgresultsHLT2Token_;

  edm::EDGetTokenT<std::vector<pat::Jet> > jet_token;
  edm::EDGetTokenT<std::vector<pat::Muon> > muon_token;
  edm::EDGetTokenT<std::vector<pat::Electron> > electron_token;
  edm::EDGetTokenT<reco::ElectronSeedCollection> l1PixelSeedsToken_;
  edm::EDGetTokenT<std::vector<pat::Photon> > photon_token;
  edm::EDGetTokenT<std::vector<reco::Vertex> > PV_token;

  edm::EDGetTokenT<double> hltFixedGridRhoFastjetAllCaloForMuons_token;
  edm::EDGetTokenT<double> rhoJetsToken_;

  edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> et_Filter_Token_;
  edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> showershape_Filter_Token_;
  edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> dphi_Filter_Token_;

  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > showershape_Var_Token_;
  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > hovere_Var_Token_;
  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > trackiso_Var_Token_;


  edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> ele32wptight_l1_Filter_Token_;
  edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> ele32wptight_et_Filter_Token_;
  edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> ele32wptight_showershape_Filter_Token_;
  edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> ele32wptight_hoe_Filter_Token_;
  edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> ele32wptight_ecaliso_Filter_Token_;
  edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> ele32wptight_hcaliso_Filter_Token_;
  edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> ele32wptight_pixelmatch_Filter_Token_;
  edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> ele32wptight_pms2_Filter_Token_;
  edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> ele32wptight_ooeminoop_Filter_Token_;
  edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> ele32wptight_missinghits_Filter_Token_;
  edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> ele32wptight_deta_Filter_Token_;
  edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> ele32wptight_dphi_Filter_Token_; 
  edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> ele32wptight_trackiso_Filter_Token_;

  //edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> ele32wptight_customtrackiso_Filter_Token_;
  //edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> ele32wptight_customtrackiso_Filter_Token_;
  //edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> ele32wptight_customtrackiso_Filter_Token_;
    
  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > >   ele32wptight_et_Var_Token_;
  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > >   ele32wptight_showershape_Var_Token_;
  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > >   ele32wptight_hovere_Var_Token_;
  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > >   ele32wptight_ecaliso_Var_Token_;
  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > >   ele32wptight_hcaliso_Var_Token_;
  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > >   ele32wptight_pixelmatch_Var_Token_;
  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > >   ele32wptight_pms2_Var_Token_;
  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > >   ele32wptight_ooeminoop_Var_Token_;
  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > >   ele32wptight_missinghits_Var_Token_;
  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > >   ele32wptight_deta_Var_Token_;
  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > >   ele32wptight_dphi_Var_Token_;
  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > >   ele32wptight_gsfcharge_Var_Token_;
  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > >   ele32wptight_gsfeta_Var_Token_;
  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > >   ele32wptight_gsfphi_Var_Token_;
  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > >   ele32wptight_gsfpt_Var_Token_;
 


  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > >   ele32wptightorig_trackiso_Var_Token_;

  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > >   ele32wptight_trackiso_Var_Token_;
  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > >   ele32wptight_customtrackiso_Var_Token_;
  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > >   ele32wptight_customecaliso_Var_Token_;
  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > >   ele32wptight_customecaliso2_Var_Token_;
  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > >   ele32wptight_customhcaliso_Var_Token_;

  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > >   ele32wptight_custom1trackiso_Var_Token_;
  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > >   ele32wptight_custom2trackiso_Var_Token_;
  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > >   ele32wptight_custom3trackiso_Var_Token_;
  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > >   ele32wptight_custom4trackiso_Var_Token_;
  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > >   ele32wptight_custom5trackiso_Var_Token_;
  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > >   ele32wptight_custom6trackiso_Var_Token_;
  edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > >   ele32wptight_custom7trackiso_Var_Token_;
  edm::EDGetTokenT<l1t::EGammaBxCollection>l1EGammaToken_;
  edm::EDGetTokenT<l1t::EGammaBxCollection>l1EGammaUnpackedToken_;
  edm::EDGetTokenT<LHEEventProduct> lheEventToken_;
  edm::EDGetTokenT<reco::GenParticleCollection> genpartToken_;

  
  edm::Service<TFileService> fs;
  TTree* outputTree;
  unsigned long _eventNb;
  unsigned long _runNb;
  unsigned long _lumiBlock;
  unsigned long _bx;

  bool HLT_Ele32_WPTight_Gsf;
  bool HLT_Ele32_WPTight_Gsf_Relax;
  bool HLT_Photon30EB_TightID_TightIso;
  bool HLT_Photon40EB_TightID_TightIso;
  bool HLT_Photon40EB_TightID_TightIso_Custom;
  bool HLT_Photon40EB_CustomTightID_TightIso;
  bool HLT_Photon40EB_DisabledTightID_TightIso;
  bool HLT_Photon50EB_TightID_TightIso;
  bool HLT_Photon55EB_TightID_TightIso;
  bool HLT_Photon75EB_TightID_TightIso;
  bool HLT_Photon90EB_TightID_TightIso;
  bool HLT_Photon110EB_TightID_TightIso;

  bool HLT_DoubleMu3_DCA_PFMET50_PFMHT60;
  bool HLT_DoubleMu3_DZ_PFMET50_PFMHT60;
  bool HLT_DoubleMu3_DCA_PFMET50_PFMHT60_Mass0p1;
  bool HLT_DoubleMu3_DCA_PFMET50_PFMHT60_Mass2p0;
  bool HLT_DoubleMu3_DCA_PFMET50_PFMHT60_Mass2p0_noDCA;
  bool HLT_IsoMu24;

  bool HLT_Diphoton15_10_TightID_ECALTrackIsoDr0p2_EBEB;
  bool HLT_DoubleEle6p5_eta1p22_mMax6;
  bool HLT_Diphoton15_10_TightID_ECALTrackIsoDr0p2to0p4_EBEB;
  bool HLT_DoubleEle15_5_CaloIdL_MW;
  bool HLT_DoubleEle25_CaloIdL_MW;

  

  bool HLT_IsoMu24_ORIG;
  bool HLT_DoubleMu3_DCA_PFMET50_PFMHT60_ORIG;
  bool HLT_Mu50_ORIG;
  bool HLT_Ele32_WPTight_Gsf_ORIG;
  bool HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_ORIG;
  bool HLT_DoubleEle25_CaloIdL_MW_ORIG;
  bool HLT_DoubleEle6p5_eta1p22_mMax6_ORIG;
  bool HLT_Photon45EB_TightID_TightIso_ORIG;
  bool HLT_Photon30EB_TightID_TightIso_ORIG;
  bool HLT_Photon50EB_TightID_TightIso_ORIG;
  
  bool HLT_Photon75EB_TightID_TightIso_ORIG;
  bool HLT_Photon90EB_TightID_TightIso_ORIG;
  bool HLT_Diphoton30_18_R9IdL_AND_HE_AND_IsoCaloId_ORIG;
  bool HLT_Diphoton22_14_eta1p5_R9IdL_AND_HET_AND_IsoTCaloIdT_ORIG;
  bool HLT_Diphoton30_22_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass90_ORIG;
  
  bool HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL_PFHT380_ORIG;
  bool HLT_Photon32_OneProng32_M50To105_ORIG;
  bool HLT_Photon60_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3_ORIG;
  bool HLT_Photon35_TwoProngs35_ORIG;
  bool HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_ORIG;


  bool HLT_Photon110EB_TightID_TightIso_ORIG;
  bool HLT_Photon33_ORIG;
  bool HLT_Photon50_ORIG;

  bool passl1singleordieg;
  vector<float> probe_ele_pt;
  vector<float> probe_ele_eta;
  vector<float> probe_ele_phi;
  vector<float> probe_ele_mll;
  
  vector<float> probe_ele_ele32wptight_pt_HLT;
  vector<float> probe_ele_ele32wptight_sietaieta_HLT;
  vector<float> probe_ele_ele32wptight_hoe_HLT;
  //vector<float> probe_ele_ele32wptight_r9_HLT;
  vector<float> probe_ele_ele32wptight_ecaliso_HLT;
  vector<float> probe_ele_ele32wptight_hcaliso_HLT;
  vector<float> probe_ele_ele32wptight_pixelmatch_HLT;
  vector<float> probe_ele_ele32wptight_pms2_HLT;
  vector<float> probe_ele_ele32wptight_ooeminoop_HLT;
  vector<float> probe_ele_ele32wptight_missinghits_HLT;
  vector<float> probe_ele_ele32wptight_deta_HLT;
  vector<float> probe_ele_ele32wptight_dphi_HLT;
  vector<float> probe_ele_ele32wptight_trackiso_HLT;
  vector<float> probe_ele_ele32wptightorig_trackiso_HLT;

  
  vector<float> probe_ele_ele32wptight_customtrackiso_HLT;
  vector<float> probe_ele_ele32wptight_custom1trackiso_HLT;
  vector<float> probe_ele_ele32wptight_custom2trackiso_HLT;
  vector<float> probe_ele_ele32wptight_custom3trackiso_HLT;
  vector<float> probe_ele_ele32wptight_custom4trackiso_HLT;
  vector<float> probe_ele_ele32wptight_custom5trackiso_HLT;
  vector<float> probe_ele_ele32wptight_custom6trackiso_HLT;
  vector<float> probe_ele_ele32wptight_custom7trackiso_HLT;
  vector<float> probe_ele_ele32wptight_customecaliso_HLT;
  vector<float> probe_ele_ele32wptight_customecaliso2_HLT;
  vector<float> probe_ele_ele32wptight_customhcaliso_HLT;
  vector<bool> probe_ele_ele32orig;
  vector<bool> probe_ele_ele12orig;
  vector<bool> probe_ele_ele12orig_l1eg12;
  vector<bool> probe_ele_ele32rehlt;
  vector<bool> probe_ele_ele12rehlt;
  vector<bool> probe_ele_ele32custom;

  vector<bool> probe_ele_ele30orig;
  vector<bool> probe_ele_ele30rehlt;
  vector<bool> probe_ele_ele30customrehlt;

  
  vector<bool> probe_ele_passphoton40origcuts;
  vector<bool> probe_ele_passphoton50origcuts;
  vector<bool> probe_ele_passphoton40customcuts_et40;
  vector<bool> probe_ele_passphoton40origcuts_et40;

  vector<float> probe_ele_ele32wptight_gsfcharge_HLT;
  vector<float> probe_ele_ele32wptight_gsfpt_HLT;
  vector<float> probe_ele_ele32wptight_gsfeta_HLT;
  vector<float> probe_ele_ele32wptight_gsfphi_HLT;


  vector<float> _phEta;
  vector<float> _phPhi;
  vector<float> _phPt;
  vector<bool> _phPassTightID;
  vector<bool> _phPassLooseID;
  vector<float>_phgIso;
  vector<float>_phchIso;
  vector<float>_phnhIso;
  vector<bool> _ph_ele32orig;
  vector<bool> _ph_ele32rehlt;
  vector<bool> _ph_ele32custom;
  vector<bool> _ph_passphoton40origcuts;
  vector<bool> _ph_passphoton50origcuts;
  vector<bool> _ph_passphoton40customcuts_et40;
  vector<bool> _ph_passphoton40origcuts_et40;


  vector <Float_t> _L1eg_pt;
  vector <Float_t> _L1eg_eta;
  vector <Float_t> _L1eg_phi;
  vector <int> _L1eg_bx;
  vector <int> _L1eg_iso;

  vector<float> hltphoton_pt;
  vector<float> hltphoton_eta;
  vector<float> hltphoton_phi;

  vector<float> hltphoton_ele32wptight_sietaieta_HLT;
  vector<float> hltphoton_ele32wptight_hoe_HLT;
  //vector<float> hltphoton_ele32wptight_r9_HLT;
  vector<float> hltphoton_ele32wptight_ecaliso_HLT;
  vector<float> hltphoton_ele32wptight_hcaliso_HLT;
  vector<float> hltphoton_ele32wptight_pixelmatch_HLT;
  vector<float> hltphoton_ele32wptight_pms2_HLT;
  vector<float> hltphoton_ele32wptight_ooeminoop_HLT;
  vector<float> hltphoton_ele32wptight_missinghits_HLT;
  vector<float> hltphoton_ele32wptight_deta_HLT;
  vector<float> hltphoton_ele32wptight_dphi_HLT;
  vector<float> hltphoton_ele32wptight_gsfcharge_HLT;
  vector<float> hltphoton_ele32wptight_gsfpt_HLT;
  vector<float> hltphoton_ele32wptight_gsfeta_HLT;
  vector<float> hltphoton_ele32wptight_gsfphi_HLT;

  vector<float> hltphoton_ele32wptight_trackiso_HLT;
  vector<float> hltphoton_ele32wptight_customtrackiso_HLT;
  vector<float> hltphoton_ele32wptight_custom1trackiso_HLT;
  vector<float> hltphoton_ele32wptight_custom2trackiso_HLT;
  vector<float> hltphoton_ele32wptight_custom3trackiso_HLT;
  vector<float> hltphoton_ele32wptight_custom4trackiso_HLT;
  vector<float> hltphoton_ele32wptight_custom5trackiso_HLT;
  vector<float> hltphoton_ele32wptight_custom6trackiso_HLT;
  vector<float> hltphoton_ele32wptight_custom7trackiso_HLT;
  vector<float> hltphoton_ele32wptight_customecaliso_HLT;
  vector<float> hltphoton_ele32wptight_customecaliso2_HLT;
  vector<float> hltphoton_ele32wptight_customhcaliso_HLT;

  Bool_t fromWZdecay;
  Float_t lhe_dielemass;
  Float_t lhe_dielept;
  Float_t lhe_dieleeta;
  Float_t lhe_dielephi;
  Float_t lhe_dieledeta;
  Float_t lhe_dieledphi;
  Float_t hlt_rho;
  Float_t rho;
  Int_t n_goodvertex;
  Int_t n_vertex;
  TH1F* h_ele32wptight_lastfilter_den;
  TH1F* h_ele32wptight_lastfilter_num;
  TH1F* h_sietaieta_HLT;
  TH1F* h_hoe_HLT;
  TH1F* h_trackiso_HLT;
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
  trigobjectsRAWORIGToken_=consumes<trigger::TriggerEvent>(edm::InputTag("hltTriggerSummaryAOD::HLT"));  
  trigobjectsRAWHLT2Token_=consumes<trigger::TriggerEvent>(edm::InputTag("hltTriggerSummaryAOD::customhltnano"));  

  trgresultsORIGToken_= consumes<edm::TriggerResults>( edm::InputTag("TriggerResults::HLT") );
  trgresultsHLT2Token_= consumes<edm::TriggerResults>( edm::InputTag("TriggerResults::customhltnano") );

  
  showershape_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaClusterShape","sigmaIEtaIEta5x5","customhltnano") );
  hovere_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaHoverE","","customhltnano") );
  trackiso_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaEleGsfTrackIso","","customhltnano")  );

  et_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEG32L1SingleEGOrEtFilter","","customhltnano") ) ;
  showershape_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEle32WPTightClusterShapeFilter","","customhltnano") );
  dphi_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEle32WPTightGsfDphiFilter","","customhltnano") );
  

  ele32wptight_et_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaCandidates","","customhltnano") ); 
  ele32wptight_showershape_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaClusterShape","sigmaIEtaIEta5x5NoiseCleaned","customhltnano") ); 
  ele32wptight_hovere_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaHoverE","","customhltnano") );
  //ele32wptight_r9_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaR9ID","","customhltnano") );
  ele32wptight_ecaliso_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaEcalPFClusterIso","","customhltnano")  );
  ele32wptight_hcaliso_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaHcalPFClusterIso","","customhltnano")  );
  
  ele32wptight_pixelmatch_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaPixelMatchVars","s2","customhltnano")  );
  ele32wptight_pms2_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaPixelMatchVars","s2","customhltnano")  );
  ele32wptight_ooeminoop_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaGsfTrackVars","OneOESuperMinusOneOP","customhltnano")  );
  ele32wptight_missinghits_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaGsfTrackVars","MissingHits","customhltnano")  );
  ele32wptight_deta_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaGsfTrackVars","DetaSeed","customhltnano")  );
  ele32wptight_dphi_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaGsfTrackVars","Dphi","customhltnano")  ); 
  ele32wptight_gsfcharge_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaGsfTrackVars","GsfCharge","customhltnano")  ); 
  ele32wptight_gsfpt_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaGsfTrackVars","GsfPt","customhltnano")  ); 
  ele32wptight_gsfeta_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaGsfTrackVars","GsfEta","customhltnano")  ); 
    ele32wptight_gsfphi_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaGsfTrackVars","GsfPhi","customhltnano")  ); 
  
  ele32wptightorig_trackiso_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaEleGsfTrackIso","","customhltnano")  );
  ele32wptight_trackiso_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaEleGsfTrackIso","","customhltnano")  );
  ele32wptight_customtrackiso_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaHollowTrackIso","","customhltnano")  );
  ele32wptight_custom1trackiso_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaHollowTrackIsoDr0p2","","customhltnano")  );
  ele32wptight_custom2trackiso_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaHollowTrackIsoDr0p2to0p4","","customhltnano")  );
  ele32wptight_custom3trackiso_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaHollowCustom3TrackIso","","customhltnano")  );
  ele32wptight_custom4trackiso_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaHollowCustom4TrackIso","","customhltnano")  );
  ele32wptight_custom5trackiso_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaHollowCustom5TrackIso","","customhltnano")  );
  ele32wptight_custom6trackiso_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaHollowCustom6TrackIso","","customhltnano")  );
  ele32wptight_custom7trackiso_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaHollowCustom7TrackIso","","customhltnano")  );
  ele32wptight_customecaliso_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaEcalPFClusterIsoDr0p2","","customhltnano")  );
  ele32wptight_customecaliso2_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaEcalPFClusterIsoDr0p2to0p4","","customhltnano")  );
  ele32wptight_customhcaliso_Var_Token_  = consumes<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > ( edm::InputTag("hltEgammaCustomHcalPFClusterIso","","customhltnano")  );



  // For standard ele32 retuning
  /*
  ele32wptight_l1_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEGL1SingleEGOrFilter","","customhltnano") ) ;
  ele32wptight_et_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEG32L1SingleEGOrEtFilter","","customhltnano") ) ;
  ele32wptight_showershape_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEle32WPTightClusterShapeRelaxFilter","","customhltnano") );
  ele32wptight_hoe_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEle32WPTightHERelaxFilter","","customhltnano") );
  
  ele32wptight_ecaliso_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEle32WPTightEcalIsoRelaxFilter","","customhltnano") );
  ele32wptight_hcaliso_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEle32WPTightHcalIsoRelaxFilter","","customhltnano") );
  
  ele32wptight_pixelmatch_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEle32WPTightPixelMatchRelaxFilter","","customhltnano") );
  ele32wptight_pms2_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEle32WPTightPMS2RelaxFilter","","customhltnano") );
  ele32wptight_ooeminoop_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEle32WPTightGsfOneOEMinusOneOPRelaxFilter","","customhltnano") );
  ele32wptight_missinghits_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEle32WPTightGsfMissingHitsRelaxFilter","","customhltnano") );
  ele32wptight_deta_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEle32WPTightGsfDetaRelaxFilter","","customhltnano") );
  ele32wptight_dphi_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEle32WPTightGsfDphiRelaxFilter","","customhltnano") );
  ele32wptight_trackiso_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEle32WPTightGsfTrackIsoRelaxFilter","","customhltnano") );
  */


  //For merged EGM studies
  ele32wptight_l1_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEGL1SingleAndDoubleEGOrFilter","","customhltnano") ) ;
  ele32wptight_et_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEle5PassFiltersEtFilter","","customhltnano") ) ;
  ele32wptight_showershape_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEle5PassFiltersClusterShapeFilter","","customhltnano") );
  ele32wptight_hoe_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEle5PassFiltersHEFilter","","customhltnano") );
  
  ele32wptight_ecaliso_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEle5PassFiltersEcalIsoFilter","","customhltnano") );
  ele32wptight_hcaliso_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEle5PassFiltersHcalIsoFilter","","customhltnano") );
  
  ele32wptight_pixelmatch_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEle5PassFiltersPixelMatchFilter","","customhltnano") );
  ele32wptight_pms2_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEle5PassFiltersPMS2Filter","","customhltnano") );
  ele32wptight_ooeminoop_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEle5PassFiltersOneOEMinusOneOPFilter","","customhltnano") );
  ele32wptight_missinghits_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEle5PassFiltersMissingHitsFilter","","customhltnano") );
  ele32wptight_deta_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEle5PassFiltersDetaFilter","","customhltnano") );
  ele32wptight_dphi_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEle5PassFiltersDphiFilter","","customhltnano") );
  ele32wptight_trackiso_Filter_Token_ = consumes<trigger::TriggerFilterObjectWithRefs> ( edm::InputTag("hltEle5PassFiltersTrackIsoFilter","","customhltnano") );
  



  l1EGammaToken_=consumes<l1t::EGammaBxCollection>( edm::InputTag("simCaloStage2Digis", "EGamma") );
  l1EGammaUnpackedToken_=consumes<l1t::EGammaBxCollection>( edm::InputTag("caloStage2Digis", "EGamma") );
  lheEventToken_=consumes<LHEEventProduct>( edm::InputTag("externalLHEProducer"));
  
  genpartToken_=consumes<reco::GenParticleCollection>(edm::InputTag("genParticles"));
  jet_token = consumes< std::vector<pat::Jet> >(edm::InputTag("slimmedJets") );
  muon_token = consumes<std::vector<pat::Muon> >(edm::InputTag("slimmedMuons") );
  electron_token = consumes<std::vector<pat::Electron> >(edm::InputTag("slimmedElectrons") );
  l1PixelSeedsToken_= consumes<reco::ElectronSeedCollection >(edm::InputTag("hltEgammaElectronPixelSeeds") );
  photon_token = consumes<std::vector<pat::Photon> >(edm::InputTag("slimmedPhotons") );
  PV_token = consumes<std::vector<reco::Vertex> > (edm::InputTag("offlineSlimmedPrimaryVertices"));
  
  hltFixedGridRhoFastjetAllCaloForMuons_token = consumes<double>(edm::InputTag("hltFixedGridRhoFastjetAllCaloForMuons","","customhltnano"));
  rhoJetsToken_ = consumes<double>(edm::InputTag("fixedGridRhoFastjetAll","",""));
  //now do what ever initialization is needed
  //   usesResource("TFileService");


  h_ele32wptight_lastfilter_den= fs->make<TH1F>("h_ele32wptight_lastfilter_den","",20,0,100);
  h_ele32wptight_lastfilter_num= fs->make<TH1F>("h_ele32wptight_lastfilter_num","",20,0,100);

  h_sietaieta_HLT= fs->make<TH1F>("h_sietaieta_HLT","",100,0,0.05);
  h_hoe_HLT= fs->make<TH1F>("h_hoe_HLT","",100,0,0.2);
  h_trackiso_HLT= fs->make<TH1F>("h_trackiso_HLT","",100,0,0.5);
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


   // ****************Part 1. Accessing some trigger information ************* 
   HLT_Ele32_WPTight_Gsf= false;
   HLT_Ele32_WPTight_Gsf_Relax= false;
   HLT_Photon30EB_TightID_TightIso= false;
   HLT_Photon40EB_TightID_TightIso= false;
   HLT_Photon40EB_TightID_TightIso_Custom= false;
   HLT_Photon40EB_CustomTightID_TightIso= false;
   HLT_Photon40EB_DisabledTightID_TightIso= false;
   HLT_Photon50EB_TightID_TightIso= false;
   HLT_Photon55EB_TightID_TightIso= false;
   HLT_Photon75EB_TightID_TightIso= false;
   HLT_Photon90EB_TightID_TightIso= false;
   HLT_Photon110EB_TightID_TightIso= false;

   HLT_DoubleMu3_DCA_PFMET50_PFMHT60= false;
   HLT_DoubleMu3_DZ_PFMET50_PFMHT60= false;
   HLT_DoubleMu3_DCA_PFMET50_PFMHT60_Mass0p1= false;
   HLT_DoubleMu3_DCA_PFMET50_PFMHT60_Mass2p0= false;
   HLT_DoubleMu3_DCA_PFMET50_PFMHT60_Mass2p0_noDCA= false;
   HLT_IsoMu24 = false;

   HLT_Diphoton15_10_TightID_ECALTrackIsoDr0p2_EBEB = false;
   HLT_Diphoton15_10_TightID_ECALTrackIsoDr0p2to0p4_EBEB = false;
   HLT_DoubleEle15_5_CaloIdL_MW = false;
   HLT_DoubleEle25_CaloIdL_MW = false;
   HLT_DoubleEle6p5_eta1p22_mMax6 = false;
   
   HLT_IsoMu24_ORIG= false;
   HLT_DoubleMu3_DCA_PFMET50_PFMHT60_ORIG= false;
   HLT_Ele32_WPTight_Gsf_ORIG= false;
   HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_ORIG= false;
   HLT_DoubleEle25_CaloIdL_MW_ORIG= false;
   HLT_DoubleEle6p5_eta1p22_mMax6_ORIG= false;
   HLT_Photon45EB_TightID_TightIso_ORIG= false;
   HLT_Mu50_ORIG= false;
   HLT_Photon30EB_TightID_TightIso_ORIG= false;
   HLT_Photon50EB_TightID_TightIso_ORIG= false;
   HLT_Photon75EB_TightID_TightIso_ORIG= false;

   HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL_PFHT380_ORIG= false;
   HLT_Photon32_OneProng32_M50To105_ORIG= false;
   HLT_Photon60_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3_ORIG= false;
   HLT_Photon35_TwoProngs35_ORIG= false;
   HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_ORIG= false;

   HLT_Photon90EB_TightID_TightIso_ORIG= false;
   HLT_Diphoton30_18_R9IdL_AND_HE_AND_IsoCaloId_ORIG= false;
   HLT_Diphoton22_14_eta1p5_R9IdL_AND_HET_AND_IsoTCaloIdT_ORIG= false;
   HLT_Diphoton30_22_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass90_ORIG= false;
   HLT_Photon110EB_TightID_TightIso_ORIG= false;
   HLT_Photon33_ORIG = false;
   HLT_Photon50_ORIG = false;

   passl1singleordieg = false;
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
	 //	 cout << "Passed path: " << TrigPath<<endl;
	 if(TrigPath.Index("HLT_IsoMu24_v") >=0) HLT_IsoMu24_ORIG=true;
	 if(TrigPath.Index("HLT_DoubleMu3_DCA_PFMET50_PFMHT60_v") >=0) HLT_DoubleMu3_DCA_PFMET50_PFMHT60_ORIG=true;
	 if(TrigPath.Index("HLT_Ele32_WPTight_Gsf_v") >=0) HLT_Ele32_WPTight_Gsf_ORIG=true;
	 if(TrigPath.Index("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_v") >=0) HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_ORIG=true;
	 if(TrigPath.Index("HLT_DoubleEle25_CaloIdL_MW_v") >=0) HLT_DoubleEle25_CaloIdL_MW_ORIG=true;
	 if(TrigPath.Index("HLT_DoubleEle6p5_eta1p22_mMax6_v") >=0) HLT_DoubleEle6p5_eta1p22_mMax6_ORIG=true;

	 if(TrigPath.Index("HLT_Mu50_v") >=0) HLT_Mu50_ORIG=true;
	 if(TrigPath.Index("HLT_Photon30EB_TightID_TightIso_v") >=0) HLT_Photon30EB_TightID_TightIso_ORIG=true;
	 if(TrigPath.Index("HLT_Photon45EB_TightID_TightIso_v") >=0) HLT_Photon45EB_TightID_TightIso_ORIG=true;
	 if(TrigPath.Index("HLT_Photon50EB_TightID_TightIso_v") >=0) HLT_Photon50EB_TightID_TightIso_ORIG=true;

	 if(TrigPath.Index("HLT_Photon75EB_TightID_TightIso_v") >=0) HLT_Photon75EB_TightID_TightIso_ORIG=true;
	 if(TrigPath.Index("HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL_PFHT380_v") >=0) HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL_PFHT380_ORIG=true;
	 if(TrigPath.Index("HLT_Photon32_OneProng32_M50To105_v") >=0) HLT_Photon32_OneProng32_M50To105_ORIG=true;
	 if(TrigPath.Index("HLT_Photon60_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3_v") >=0) HLT_Photon60_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3_ORIG=true;
	 if(TrigPath.Index("HLT_Photon35_TwoProngs35_v") >=0) HLT_Photon35_TwoProngs35_ORIG=true;
	 if(TrigPath.Index("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_v") >=0) HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_ORIG=true;
	 if(TrigPath.Index("HLT_Photon90EB_TightID_TightIso_v") >=0) HLT_Photon90EB_TightID_TightIso_ORIG=true;
	 if(TrigPath.Index("HLT_Diphoton30_18_R9IdL_AND_HE_AND_IsoCaloId_v") >=0) HLT_Diphoton30_18_R9IdL_AND_HE_AND_IsoCaloId_ORIG=true;
	 if(TrigPath.Index("HLT_Diphoton22_14_eta1p5_R9IdL_AND_HET_AND_IsoTCaloIdT_v") >=0) HLT_Diphoton22_14_eta1p5_R9IdL_AND_HET_AND_IsoTCaloIdT_ORIG=true;
	 if(TrigPath.Index("HLT_Diphoton30_22_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass90_v") >=0) HLT_Diphoton30_22_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass90_ORIG=true;


	 if(TrigPath.Index("HLT_Photon110EB_TightID_TightIso_v") >=0) HLT_Photon110EB_TightID_TightIso_ORIG=true; 
	 if(TrigPath.Index("HLT_Photon33_v") >=0) HLT_Photon33_ORIG=true;
         if(TrigPath.Index("HLT_Photon50_v") >=0) HLT_Photon50_ORIG=true;

	 //Notice the special syntax: since the path version can change during data taking one only looks for the string "HLT_Ele32_WPTight_Gsf_v"
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
	 //	 cout << "Passed path: " << TrigPath<<endl;
	 if(TrigPath.Index("HLT_Ele32_WPTight_Gsf_v") >=0) HLT_Ele32_WPTight_Gsf=true;
	 if(TrigPath.Index("HLT_Ele32_WPTight_Gsf_Relax_v") >=0) HLT_Ele32_WPTight_Gsf_Relax=true;
	 if(TrigPath.Index("HLT_IsoMu24_v") >=0) HLT_IsoMu24=true;
	 if(TrigPath.Index("HLT_Photon30EB_TightID_TightIso_v") >=0) HLT_Photon30EB_TightID_TightIso=true;
	 if(TrigPath.Index("HLT_Photon40EB_TightID_TightIso_v") >=0) HLT_Photon40EB_TightID_TightIso=true;
	 if(TrigPath.Index("HLT_Photon40EB_TightID_TightIso_Custom_v") >=0) HLT_Photon40EB_TightID_TightIso_Custom=true;
	 if(TrigPath.Index("HLT_Photon40EB_CustomTightID_TightIso_v") >=0) HLT_Photon40EB_CustomTightID_TightIso=true;
	 if(TrigPath.Index("HLT_Photon40EB_DisabledTightID_TightIso_v") >=0) HLT_Photon40EB_DisabledTightID_TightIso=true;
	 if(TrigPath.Index("HLT_Photon50EB_TightID_TightIso_v") >=0) HLT_Photon50EB_TightID_TightIso=true;
	 if(TrigPath.Index("HLT_Photon55EB_TightID_TightIso_v") >=0) HLT_Photon55EB_TightID_TightIso=true;
	 if(TrigPath.Index("HLT_Photon75EB_TightID_TightIso_v") >=0) HLT_Photon75EB_TightID_TightIso=true;
	 if(TrigPath.Index("HLT_Photon90EB_TightID_TightIso_v") >=0) HLT_Photon90EB_TightID_TightIso=true;
	 if(TrigPath.Index("HLT_Photon110EB_TightID_TightIso_v") >=0) HLT_Photon110EB_TightID_TightIso=true; 

	 if(TrigPath.Index("HLT_DoubleMu3_DCA_PFMET50_PFMHT60_v") >=0) HLT_DoubleMu3_DCA_PFMET50_PFMHT60=true; 
	 if(TrigPath.Index("HLT_DoubleMu3_DZ_PFMET50_PFMHT60_v") >=0) HLT_DoubleMu3_DZ_PFMET50_PFMHT60=true; 
	 if(TrigPath.Index("HLT_DoubleMu3_DCA_PFMET50_PFMHT60_Mass0p1_v") >=0) HLT_DoubleMu3_DCA_PFMET50_PFMHT60_Mass0p1=true; 
	 if(TrigPath.Index("HLT_DoubleMu3_DCA_PFMET50_PFMHT60_Mass2p0_v") >=0) HLT_DoubleMu3_DCA_PFMET50_PFMHT60_Mass2p0=true; 
	 if(TrigPath.Index("HLT_DoubleMu3_DCA_PFMET50_PFMHT60_Mass2p0_noDCA_v") >=0) HLT_DoubleMu3_DCA_PFMET50_PFMHT60_Mass2p0_noDCA=true;

	 if(TrigPath.Index("HLT_Diphoton15_10_TightID_ECALTrackIsoDr0p2_EBEB_v") >=0) HLT_Diphoton15_10_TightID_ECALTrackIsoDr0p2_EBEB=true;
	 if(TrigPath.Index("HLT_Diphoton15_10_TightID_ECALTrackIsoDr0p2to0p4_EBEB_v") >=0) HLT_Diphoton15_10_TightID_ECALTrackIsoDr0p2to0p4_EBEB=true;
	 if(TrigPath.Index("HLT_DoubleEle15_5_CaloIdL_MW_v") >=0) HLT_DoubleEle15_5_CaloIdL_MW=true;
	 if(TrigPath.Index("HLT_DoubleEle25_CaloIdL_MW_v") >=0) HLT_DoubleEle25_CaloIdL_MW=true;
	 if(TrigPath.Index("HLT_DoubleEle6p5_eta1p22_mMax6_v") >=0) HLT_DoubleEle6p5_eta1p22_mMax6=true;
	 
	 //Notice the special syntax: since the path version can change during data taking one only looks for the string "HLT_Ele32_WPTight_Gsf_v"
       }
     }
   }
   
   

   //L1 EG
   
   edm::Handle<l1t::EGammaBxCollection> l1egcoll;
   iEvent.getByToken(l1EGammaToken_ , l1egcoll);
   if(!l1egcoll.isValid()) { 
     iEvent.getByToken(l1EGammaUnpackedToken_ , l1egcoll);
     //  cout << "!l1egcoll.isValid()"<<endl;
   }
   
   if( !l1egcoll.failedToGet() ) {
     for(int i = l1egcoll->getFirstBX() ; i<= l1egcoll->getLastBX() ;i++){
       for( l1t::EGammaBxCollection::const_iterator l1egit= l1egcoll->begin(i); l1egit != l1egcoll->end(i) ; ++l1egit){
	 //	 cout << "L1 eg " <<l1egit->pt()<< ", " <<l1egit->eta()<<endl;
	 if(l1egit->pt()<10||i!=0) continue;
	 _L1eg_pt.push_back( l1egit->pt() );
	 _L1eg_eta.push_back( l1egit->eta() );
	 _L1eg_phi.push_back( l1egit->phi() );
	 _L1eg_bx.push_back( i);
	 _L1eg_iso.push_back( l1egit->hwIso());
       }
     }
   }
   else {
     cout << "!l1egcoll.failedToGet() "<<endl;
   }

   
   for (unsigned int iteg = 0;  iteg < _L1eg_phi.size(); iteg++){
     if(_L1eg_pt[iteg]<15)continue;
     if(_L1eg_pt[iteg]>=30) {passl1singleordieg = true; break;}
     
     for (unsigned int iteg2 = 0;  iteg2 < _L1eg_phi.size(); iteg2++){
       if(iteg == iteg2) continue;
       if(_L1eg_pt[iteg2]<11)continue;
       if(_L1eg_pt[iteg]>20&&_L1eg_pt[iteg2]>12) {passl1singleordieg =	true; break;}

       double dphi = acos(cos(_L1eg_phi[iteg]-_L1eg_phi[iteg2]));
       double deta = _L1eg_eta[iteg]-_L1eg_eta[iteg2];
       double dr = sqrt(dphi*dphi+deta*deta);
       if(abs(_L1eg_eta[iteg])>1.5)continue;
       if(abs(_L1eg_eta[iteg2])>1.5)continue;
       if(dr<0.6) {passl1singleordieg =  true; break;}
       if(deta<1.5&&_L1eg_pt[iteg2]>=15) {passl1singleordieg =  true; break;}
     }
   }

   
   //LHE info

   edm::Handle<LHEEventProduct> lhe_handle;
   iEvent.getByToken(lheEventToken_, lhe_handle);
   lhe_dielemass = -1;
   lhe_dielept = -1;
   lhe_dieleeta = -1;
   lhe_dielephi = -1;
   lhe_dieledphi = -99;
   lhe_dieledeta = -99;
   fromWZdecay = false;
   if (lhe_handle.isValid()){ 
     std::vector<lhef::HEPEUP::FiveVector> lheParticles = lhe_handle->hepeup().PUP;
     for (unsigned i = 0; i < lheParticles.size(); ++i) {
       ROOT::Math::PxPyPzEVector cand_ = ROOT::Math::PxPyPzEVector(lheParticles[i][0],lheParticles[i][1],lheParticles[i][2],lheParticles[i][3]);
       
       if(fabs( lhe_handle->hepeup().IDUP[i]) ==23 ){
	 lhe_dielemass = cand_.mass();
	 lhe_dielept = cand_.pt();
	 lhe_dieleeta = cand_.eta();
	 lhe_dielephi = cand_.phi();
	 
       }
       
     }
   }
   //Gen particle info
   
   edm::Handle<reco::GenParticleCollection> TheGenParticles;
   iEvent.getByToken(genpartToken_, TheGenParticles);
   int ngeneles(0), ngenposis(0);
   if(TheGenParticles.isValid()){
    
     for(reco::GenParticleCollection::const_reverse_iterator p = TheGenParticles->rbegin() ; p != TheGenParticles->rend() ; p++ ) {
       if(p->pdgId() !=11 ) continue;
       if(p->status() != 1) continue;
       if(p->pt()<2)continue;
       ngeneles ++;
       if(p->pt()<5)continue; 
       
       for(reco::GenParticleCollection::const_reverse_iterator p2 = TheGenParticles->rbegin() ; p2 != TheGenParticles->rend() ; p2++ ) {
	 if(p2->pdgId() !=-11 ) continue;
	 if(p2->status() != 1) continue;
	 if(p2->pt()<2)continue;
	 ngenposis++;
	 if(p2->pt()<5)continue;

	 fromWZdecay = (p->isPromptFinalState()||p->isDirectPromptTauDecayProductFinalState()) &&(p2->isPromptFinalState()||p2->isDirectPromptTauDecayProductFinalState());

	 TLorentzVector e1, e2;
	 e1.SetPtEtaPhiE(p->pt(), p->eta(), p->phi(), p->energy());
	 e2.SetPtEtaPhiE(p2->pt(), p2->eta(), p2->phi(), p2->energy());
	 
	 if(lhe_dielemass==-1){
	   lhe_dielemass=(e1+e2).Mag();
	   lhe_dielept=(e1+e2).Pt();
	   lhe_dieleeta=(e1+e2).Eta();
	   lhe_dielephi=(e1+e2).Phi();

	   lhe_dieledphi=abs(acos(cos(e1.Phi()-e2.Phi())));
	   lhe_dieledeta=abs(e1.Eta()-e2.Eta());

	 }
	 
	 
       }
     }
     
   }
   if(ngeneles+ngenposis!=2) lhe_dielemass=-1;
 

   //Exercise 1: 
   //Clone and *then* modify the code above in order to save the decision of your customized HLT menu in the booleans HLT_Mu3_PFJet200DeepCSV_1p59, HLT_Mu3_L1SingleJet180, HLT_PFJet200DeepCSV_1p59
   //Do not directly edit the code above as you will also need the use the original HLT_Ele32_WPTight_Gsf decision later on.

   


   if(useMINIAOD){
   //Accessing the trigger objects in MINIAOD
   //This recipe works for MINIAOD only
   edm::Handle<pat::TriggerObjectStandAloneCollection> triggerObjects;
   iEvent.getByToken(trigobjectsMINIAODToken_, triggerObjects);

   const edm::TriggerNames &names = iEvent.triggerNames(*trigResults);
   for (pat::TriggerObjectStandAlone obj : *triggerObjects) {
     obj.unpackFilterLabels(iEvent,*trigResults);
     obj.unpackPathNames(names);
     for (unsigned h = 0; h < obj.filterLabels().size(); ++h){
       string myfillabl=obj.filterLabels()[h];
       //cout << "Trigger object name, pt, eta, phi: "
       //	    << myfillabl<<", " << obj.pt()<<", "<<obj.eta()<<", "<<obj.phi() << endl;
     }
   }
   }
   //Exercise 2: uncomment the lines above to print all the trigger objects and their corresponding pt, eta, phi. 
   

   //Accessing the trigger objects in RAW/AOD
   //Printing here all trigger objects corresponding to the filter hltL3MuFiltered3
   edm::Handle<trigger::TriggerEvent> triggerObjectsSummary;
   iEvent.getByToken(trigobjectsRAWORIGToken_ ,triggerObjectsSummary);
   trigger::TriggerObjectCollection selectedObjects;
   if (triggerObjectsSummary.isValid()) {
     size_t filterIndex = (*triggerObjectsSummary).filterIndex( edm::InputTag("hltL3MuFiltered3","","HLT") );
     trigger::TriggerObjectCollection allTriggerObjects = triggerObjectsSummary->getObjects();
     if (filterIndex < (*triggerObjectsSummary).sizeFilters()) { 
       const trigger::Keys &keys = (*triggerObjectsSummary).filterKeys(filterIndex);
       for (size_t j = 0; j < keys.size(); j++) {
	 //trigger::TriggerObject foundObject = (allTriggerObjects)[keys[j]];
	 //cout <<"object found, printing pt, eta, phi: " <<foundObject.pt()<<", "<<foundObject.eta()<<", "<< foundObject.phi() <<endl;
       }
     }
   }
   
   //Exercise 3: uncomment the two lines above and modify the input tag to print all trigger objects corresponding to the last filter of the HLT_Mu3_PFJet200DeepCSV_1p59 path (btagged jet with pt>200 GeV)



   // **************** Part 2. Accessing some offline information ************** 
   
   //What you really want to do is to assess the trigger performances on top of an offline selection. 
    


   /*
   //Offline jets
   //Find the highest pt b jet (medium WP i.e. csv>0.8484 for b tagging) in the event.
   //Find the highest csv of a jet with pt>250 GeV in the event.
   //Count the nb of bjets with pt>200 GeV in the event
   edm::Handle< std::vector<pat::Jet> > jets;
   iEvent.getByToken(jet_token,jets );

   double leadingbjetpt(-100), leadingbjeteta(-100),leadingbjetphi(-100); 
   double highestcsv_jetpt250 =-1;
   int nbjetspt200 = 0;
   for( std::vector<pat::Jet>::const_iterator jet = (*jets).begin(); jet != (*jets).end(); jet++ ) {
     double ptjet = jet->pt();
     double etajet = jet->eta();
     double phijet = jet->phi();
     double csvjet = jet->bDiscriminator("pfDeepCSVJetTags:probb")+ jet->bDiscriminator("pfDeepCSVJetTags:probbb");//cf https://twiki.cern.ch/twiki/bin/viewauth/CMS/BtagRecommendation102X
     //The next following lines just remove e/mu from (semi)leptonic ttbar. 
     if( jet->muonEnergyFraction() >0.7)continue;
     if( jet->electronEnergyFraction() >0.7)continue;
     
     if(abs( etajet)>2.4) continue; //Only consider jets in tracker acceptance since we want to do b tagging. 
     if(csvjet>0.4184&& ptjet>leadingbjetpt) { leadingbjetpt = ptjet; leadingbjeteta =etajet; leadingbjetphi = phijet;} 
     if(ptjet>250&& csvjet>highestcsv_jetpt250) { highestcsv_jetpt250 = csvjet;} 
     if(csvjet>0.4184&& ptjet>200) { nbjetspt200++; } 
   }

   
   //Offline muons 
   edm::Handle< std::vector<pat::Muon> > muons;
   iEvent.getByToken(muon_token,muons );
   //We also need the vertices here
   //Count the nb of offline muons with pt >3
   //Find the highest pt muon
   int nmuonspt3 =0; 
   double leadingmuonpt(-10),leadingmuoneta(-10),leadingmuonphi(-10);
   for( std::vector<pat::Muon>::const_iterator muon = (*muons).begin(); muon != (*muons).end(); muon++ ) {
   if(!PassOfflineMuonSelection(&*muon,PV)) continue;
     double ptmuon = muon->pt();
     double etamuon = muon->eta();
     double phimuon = muon->phi();
     if(ptmuon>=3) nmuonspt3++;
     if(ptmuon>leadingmuonpt){leadingmuonpt=ptmuon;leadingmuoneta=etamuon;leadingmuonphi=phimuon;}
   }

   */
   
   //We can now fill some histograms (numerator and denominator to study the efficiency of our favourite path).
   //Here we factorize the muon and jet legs and measure their efficiencies separately
    

   /*
   //Effcy vs pt of the leading b jet: 
   h_mu3pfjet200deepcsv1p59_vs_leadbjetpt_den->Fill(leadingbjetpt);
   if(passHLT_Mu3_PFJet200DeepCSV_1p59) h_mu3pfjet200deepcsv1p59_vs_leadbjetpt_num->Fill(leadingbjetpt);
   if(passHLT_Mu3_L1SingleJet180) h_mu3pfjet200deepcsv1p59_vs_leadbjetpt_numl1->Fill(leadingbjetpt); //For L1 turn on only

   //Effcy vs the highest csv of jet with pt>250:
   h_mu3pfjet200deepcsv1p59_vs_highestcsv_jetpt250_den->Fill(highestcsv_jetpt250);
   if(passHLT_Mu3_PFJet200DeepCSV_1p59) h_mu3pfjet200deepcsv1p59_vs_highestcsv_jetpt250_num->Fill(highestcsv_jetpt250);


   //Effcy vs nb of bjets with pt>200 
   h_mu3pfjet200deepcsv1p59_vs_nbjetspt200_den->Fill(nbjetspt200);
   if(passHLT_Mu3_PFJet200DeepCSV_1p59) h_mu3pfjet200deepcsv1p59_vs_nbjetspt200_num->Fill(nbjetspt200);

   //Effcy vs leading muon pt:
   h_mu3pfjet200deepcsv1p59_vs_leadingmuonpt_den->Fill(leadingmuonpt);
   if(passHLT_Mu3_PFJet200DeepCSV_1p59) h_mu3pfjet200deepcsv1p59_vs_leadingmuonpt_num->Fill(leadingmuonpt);

   //Exercise 4: Define the denominator (offline selection) for the histograms filled above and look at the obtained efficiency plots. 
   //For this exercise, you need to run on at least 10k events in order to start to see the jet turn on. 
   */

   
   //Exercise 5: Take a look at the histograms obtained in the following root file, with much higher stat: 
   ///afs/cern.ch/work/l/lathomas/public/HLTTutorial_27Oct2017/OutputFiles/out_singlemuon_highstat.root
   //Check the efficiency vs the leading jet pt. 

   //Questions: 
   //- Would you say that the plateau efficiency represents the probability for a b quark jet to fire the b tagging condition at HLT? 
   //- Do you understand why the efficiency increases with the n(bjets)? 
   //-Is the efficiency measured vs muon pt unbiased when running on a SingleMuon dataset?  


   
   

   //Let's finally see a Tag and Probe example on Z(ee)
   //Offline electrons
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
   iEvent.getByToken(electron_token,electrons );


   //First loop to find a tag electron
   for( std::vector<pat::Electron>::const_iterator tagele = (*electrons).begin(); tagele != (*electrons).end(); tagele++ ) {
     if(!PassOfflineElectronSelection(&*tagele,PV)) continue;
     double pttagele = tagele->pt();
     double etatagele = tagele->eta();
     double phitagele = tagele->phi();
     if(pttagele<32) continue; 
     if(!RecoHLTMatchingORIG(iEvent,etatagele,phitagele,"hltEle32WPTightGsfTrackIsoFilter") ) continue;
     //We want to match the tag to the last filter of the HLT_Ele32_WPTight_Gsf
     //Take a look at  HLTrigger/Configuration/python/HLT_TutoEle32WPTight_cff.py to confirm that "hltEle32WPTightGsfTrackIsoFilter" is indeed the last filter of that path
     
     //Second loop on the probe
     for( std::vector<pat::Electron>::const_iterator probeele = (*electrons).begin(); probeele != (*electrons).end(); probeele++ ) {
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
       h_ele32wptight_lastfilter_den->Fill(ptprobeele);
       if(RecoHLTMatchingORIG(iEvent,etaprobeele,phiprobeele,"hltEle32WPTightGsfTrackIsoFilter") ) h_ele32wptight_lastfilter_num->Fill(ptprobeele);

       
       //Note that everything above is done on miniAOD.
       //If you want to do something similar for a new path, then you need to rerun HLT from RAW (obviously) and modify a bit the RecoHLTMatchingORIG function when you retrieve the trigger objects. 
       //The previous examples should make it clear on how to do that. 

     
       
       //Now, new (advanced) topic: access the HLT ID variables for an electron/photon.
       //These are typically not stored, so you have to rerun HLT. 
       //The various filters in the Single electron triggers are (in that order): Et cut, sigmaietaieta cut, H/E cut, ..., dphi cut, track iso cut
       //We will take advantage that all these cuts are applied using the same EDFilter http://cmslxr.fnal.gov/source/HLTrigger/Egamma/src/HLTGeneric(QuadraticEta)Filter.cc 
       //Here we will check the distribution of each variable just before the cut is applied. 
       //For that we will need to specify the variable name and the previous filter name. All the work is done in this VarStudied function which essentially copies what is done in HLTGeneric(QuadraticEta)Filter
       
       
       bool  dividebyE = false; bool dividebyEt = false; 
       //First pt
       //double pt_HLT = VarStudied(iEvent, etaprobeele,phiprobeele,et_Var_Token_,l1_Filter_Token_ ,dividebyE, dividebyEt);
       
       //First sietaieta
       double sietaieta_HLT = VarStudied(iEvent, etaprobeele,phiprobeele,showershape_Var_Token_,et_Filter_Token_ ,dividebyE, dividebyEt);
       h_sietaieta_HLT->Fill(sietaieta_HLT);
       //Next: H/E:
       dividebyE = true; dividebyEt = false; //For H/E
       double hoe_HLT  = VarStudied(iEvent, etaprobeele,phiprobeele,hovere_Var_Token_,showershape_Filter_Token_ ,dividebyE, dividebyEt);
       h_hoe_HLT->Fill(hoe_HLT);
       //Finally: trackiso 
       dividebyE =false; dividebyEt = true; //For isolation 
       double trackiso_HLT  = VarStudied(iEvent, etaprobeele,phiprobeele,trackiso_Var_Token_,dphi_Filter_Token_ ,dividebyE, dividebyEt);
       h_trackiso_HLT->Fill(trackiso_HLT);
       
       double pt_HLT = VarStudied(iEvent, etaprobeele,phiprobeele, ele32wptight_showershape_Var_Token_,ele32wptight_l1_Filter_Token_ ,dividebyE, dividebyEt, 0.3, true);

       dividebyE = false;  dividebyEt = false; 
       double ele32wptight_sietaieta_HLT = VarStudied(iEvent, etaprobeele,phiprobeele,ele32wptight_showershape_Var_Token_,ele32wptight_et_Filter_Token_ ,dividebyE, dividebyEt);
       dividebyE = true; dividebyEt = false;
       double ele32wptight_hoe_HLT  = VarStudied(iEvent, etaprobeele,phiprobeele,ele32wptight_hovere_Var_Token_,ele32wptight_showershape_Filter_Token_ ,dividebyE, dividebyEt);
       //dividebyE = false;  dividebyEt = false;
       //       double ele32wptight_r9_HLT  = VarStudied(iEvent, etaprobeele,phiprobeele,ele32wptight_r9_Var_Token_,ele32wptight_hoe_Filter_Token_ ,dividebyE, dividebyEt);
       dividebyE =false; dividebyEt = true;
       double ele32wptight_ecaliso_HLT  = VarStudied(iEvent, etaprobeele,phiprobeele,ele32wptight_ecaliso_Var_Token_,ele32wptight_hoe_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_hcaliso_HLT  = VarStudied(iEvent, etaprobeele,phiprobeele,ele32wptight_hcaliso_Var_Token_,ele32wptight_ecaliso_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_trackiso_HLT  = VarStudied(iEvent, etaprobeele,phiprobeele,ele32wptight_trackiso_Var_Token_,ele32wptight_hcaliso_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptightorig_trackiso_HLT  = VarStudied(iEvent, etaprobeele,phiprobeele,ele32wptightorig_trackiso_Var_Token_,ele32wptight_et_Filter_Token_ ,dividebyE, dividebyEt);
       
       dividebyE = false;  dividebyEt = false;
       double ele32wptight_pixelmatch_HLT  =  PixelMatchVariable(iEvent, etaprobeele,phiprobeele,ele32wptight_hcaliso_Filter_Token_);
	 //VarStudied(iEvent,etaprobeele,phiprobeele,ele32wptight_pixelmatch_Var_Token_, ele32wptight_hcaliso_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_pms2_HLT  = VarStudied(iEvent, etaprobeele,phiprobeele,ele32wptight_pms2_Var_Token_,ele32wptight_pixelmatch_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_ooeminoop_HLT  = VarStudied(iEvent, etaprobeele,phiprobeele,ele32wptight_ooeminoop_Var_Token_,ele32wptight_pms2_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_missinghits_HLT  = VarStudied(iEvent, etaprobeele,phiprobeele,ele32wptight_missinghits_Var_Token_,ele32wptight_ooeminoop_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_deta_HLT  = VarStudied(iEvent, etaprobeele,phiprobeele,ele32wptight_deta_Var_Token_,ele32wptight_missinghits_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_dphi_HLT  = VarStudied(iEvent, etaprobeele,phiprobeele,ele32wptight_dphi_Var_Token_,ele32wptight_deta_Filter_Token_ ,dividebyE, dividebyEt); 


       double ele32wptight_gsfcharge_HLT  = VarStudied(iEvent, etaprobeele,phiprobeele,ele32wptight_gsfcharge_Var_Token_,ele32wptight_deta_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_gsfpt_HLT  = VarStudied(iEvent, etaprobeele,phiprobeele,ele32wptight_gsfpt_Var_Token_,ele32wptight_deta_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_gsfeta_HLT  = VarStudied(iEvent, etaprobeele,phiprobeele,ele32wptight_gsfeta_Var_Token_,ele32wptight_deta_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_gsfphi_HLT  = VarStudied(iEvent, etaprobeele,phiprobeele,ele32wptight_gsfphi_Var_Token_,ele32wptight_deta_Filter_Token_ ,dividebyE, dividebyEt);

       
       dividebyE =false; dividebyEt = true;
       double ele32wptight_customtrackiso_HLT  = VarStudied(iEvent, etaprobeele,phiprobeele,ele32wptight_customtrackiso_Var_Token_,ele32wptight_hcaliso_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_custom1trackiso_HLT  = VarStudied(iEvent, etaprobeele,phiprobeele,ele32wptight_custom1trackiso_Var_Token_,ele32wptight_hcaliso_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_custom2trackiso_HLT  = VarStudied(iEvent, etaprobeele,phiprobeele,ele32wptight_custom2trackiso_Var_Token_,ele32wptight_hcaliso_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_custom3trackiso_HLT  = VarStudied(iEvent, etaprobeele,phiprobeele,ele32wptight_custom3trackiso_Var_Token_,ele32wptight_hcaliso_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_custom4trackiso_HLT  = VarStudied(iEvent, etaprobeele,phiprobeele,ele32wptight_custom4trackiso_Var_Token_,ele32wptight_hcaliso_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_custom5trackiso_HLT  = VarStudied(iEvent, etaprobeele,phiprobeele,ele32wptight_custom5trackiso_Var_Token_,ele32wptight_hcaliso_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_custom6trackiso_HLT  = VarStudied(iEvent, etaprobeele,phiprobeele,ele32wptight_custom6trackiso_Var_Token_,ele32wptight_hcaliso_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_custom7trackiso_HLT  = VarStudied(iEvent, etaprobeele,phiprobeele,ele32wptight_custom7trackiso_Var_Token_,ele32wptight_hcaliso_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_customecaliso_HLT  = VarStudied(iEvent, etaprobeele,phiprobeele,ele32wptight_customecaliso_Var_Token_,ele32wptight_hoe_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_customecaliso2_HLT  = VarStudied(iEvent, etaprobeele,phiprobeele,ele32wptight_customecaliso2_Var_Token_,ele32wptight_hoe_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_customhcaliso_HLT  = VarStudied(iEvent, etaprobeele,phiprobeele,ele32wptight_customhcaliso_Var_Token_,ele32wptight_ecaliso_Filter_Token_ ,dividebyE, dividebyEt);

       probe_ele_pt.push_back(ptprobeele);
       probe_ele_eta.push_back(etaprobeele);
       probe_ele_phi.push_back(phiprobeele);
       probe_ele_mll.push_back(mass);

       probe_ele_ele32wptight_pt_HLT.push_back(pt_HLT);
       probe_ele_ele32wptight_sietaieta_HLT.push_back(ele32wptight_sietaieta_HLT);
       
       probe_ele_ele32wptight_hoe_HLT.push_back(ele32wptight_hoe_HLT);
       //       probe_ele_ele32wptight_r9_HLT.push_back(ele32wptight_r9_HLT);
       probe_ele_ele32wptight_ecaliso_HLT.push_back(ele32wptight_ecaliso_HLT);
       probe_ele_ele32wptight_hcaliso_HLT.push_back(ele32wptight_hcaliso_HLT);
       probe_ele_ele32wptight_pixelmatch_HLT.push_back(ele32wptight_pixelmatch_HLT);
       probe_ele_ele32wptight_pms2_HLT.push_back(ele32wptight_pms2_HLT);
       probe_ele_ele32wptight_ooeminoop_HLT.push_back(ele32wptight_ooeminoop_HLT);
       probe_ele_ele32wptight_missinghits_HLT.push_back(ele32wptight_missinghits_HLT);
       probe_ele_ele32wptight_deta_HLT.push_back(ele32wptight_deta_HLT);
       probe_ele_ele32wptight_dphi_HLT.push_back(ele32wptight_dphi_HLT);
       probe_ele_ele32wptight_trackiso_HLT.push_back(ele32wptight_trackiso_HLT);
       probe_ele_ele32wptightorig_trackiso_HLT.push_back(ele32wptightorig_trackiso_HLT);
       probe_ele_ele32wptight_customtrackiso_HLT.push_back(ele32wptight_customtrackiso_HLT);
       probe_ele_ele32wptight_custom1trackiso_HLT.push_back(ele32wptight_custom1trackiso_HLT);
       probe_ele_ele32wptight_custom2trackiso_HLT.push_back(ele32wptight_custom2trackiso_HLT);
       probe_ele_ele32wptight_custom3trackiso_HLT.push_back(ele32wptight_custom3trackiso_HLT);
       probe_ele_ele32wptight_custom4trackiso_HLT.push_back(ele32wptight_custom4trackiso_HLT);
       probe_ele_ele32wptight_custom5trackiso_HLT.push_back(ele32wptight_custom5trackiso_HLT);
       probe_ele_ele32wptight_custom6trackiso_HLT.push_back(ele32wptight_custom6trackiso_HLT);
       probe_ele_ele32wptight_custom7trackiso_HLT.push_back(ele32wptight_custom7trackiso_HLT);
       probe_ele_ele32wptight_customecaliso_HLT.push_back(ele32wptight_customecaliso_HLT);
       probe_ele_ele32wptight_customecaliso2_HLT.push_back(ele32wptight_customecaliso2_HLT);
       probe_ele_ele32wptight_customhcaliso_HLT.push_back(ele32wptight_customhcaliso_HLT);


       probe_ele_ele32orig.push_back(RecoHLTMatchingORIG(iEvent,etaprobeele,phiprobeele,"hltEle32WPTightGsfTrackIsoFilter") );
       probe_ele_ele32rehlt.push_back(RecoHLTMatchingHLT2(iEvent,etaprobeele,phiprobeele,"hltEle32WPTightGsfTrackIsoFilter") );
       probe_ele_ele30orig.push_back(RecoHLTMatchingORIG(iEvent,etaprobeele,phiprobeele,"hltEle30WPTightGsfTrackIsoFilter") );
       probe_ele_ele30rehlt.push_back(RecoHLTMatchingHLT2(iEvent,etaprobeele,phiprobeele,"hltEle10WPTightGsfTrackIsoFilter") );
       probe_ele_ele30customrehlt.push_back(RecoHLTMatchingHLT2(iEvent,etaprobeele,phiprobeele,"hltEle10WPTightGsfCustomTrackIsoFilter") );


       probe_ele_ele32wptight_gsfcharge_HLT.push_back(ele32wptight_gsfcharge_HLT);
       probe_ele_ele32wptight_gsfpt_HLT.push_back(ele32wptight_gsfpt_HLT);
       probe_ele_ele32wptight_gsfeta_HLT.push_back(ele32wptight_gsfeta_HLT);
       probe_ele_ele32wptight_gsfphi_HLT.push_back(ele32wptight_gsfphi_HLT);
       

       bool passinghltEle23Ele12CaloIdLTrackIdLIsoVLTrackIsoLeg2Filter = RecoHLTMatchingORIG(iEvent,etaprobeele,phiprobeele,"hltEle23Ele12CaloIdLTrackIdLIsoVLTrackIsoLeg2Filter") ;
       bool matcheg12 = false;
       for (unsigned int iteg = 0;  iteg < _L1eg_phi.size(); iteg++){
	 if(_L1eg_pt[iteg]<12)continue; 
	 double dphi = acos(cos(_L1eg_phi[iteg]-phiprobeele));
	 double deta = _L1eg_eta[iteg]-etaprobeele;
	 double dr = sqrt(dphi*dphi+deta*deta);
	 if(dr<0.3) matcheg12 = true;
       }
       probe_ele_ele12orig.push_back(passinghltEle23Ele12CaloIdLTrackIdLIsoVLTrackIsoLeg2Filter);
       probe_ele_ele12orig_l1eg12.push_back(passinghltEle23Ele12CaloIdLTrackIdLIsoVLTrackIsoLeg2Filter&&matcheg12);
       //       probe_ele_ele12rehlt.push_back(RecoHLTMatchingHLT2(iEvent,etaprobeele,phiprobeele,"hltEle23Ele12CaloIdLTrackIdLIsoVLTrackIsoLeg2Filter") );
       probe_ele_ele32custom.push_back(RecoHLTMatchingORIG(iEvent,etaprobeele,phiprobeele,"hltEle32WPTightGsfTrackIsoRelaxFilter") );
       probe_ele_passphoton40origcuts.push_back(RecoHLTMatchingHLT2(iEvent,etaprobeele,phiprobeele,"hltEG40EBTightIDTightIsoTrackIsoFilter") );
       probe_ele_passphoton50origcuts.push_back(RecoHLTMatchingHLT2(iEvent,etaprobeele,phiprobeele,"hltEG50EBTightIDTightIsoTrackIsoFilter") );

       probe_ele_passphoton40customcuts_et40.push_back(RecoHLTMatchingHLT2(iEvent,etaprobeele,phiprobeele,"hltEG40CustomEBTightIDTightIsoEtFilter") );
       probe_ele_passphoton40origcuts_et40.push_back(RecoHLTMatchingHLT2(iEvent,etaprobeele,phiprobeele,"hltEG40EBTightIDTightIsoEtFilter") );

       

     }
   }

   edm::Handle<double> rhoJets;
   iEvent.getByToken(rhoJetsToken_,rhoJets);
   rho = *rhoJets;
   

   edm::Handle< std::vector<pat::Photon> > photons;
   iEvent.getByToken(photon_token,photons );
   for( std::vector<pat::Photon>::const_iterator ph = (*photons).begin(); ph != (*photons).end(); ph++ ) {
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
     double gIso =  (&*ph)->photonIso();

     _phgIso.push_back(gIso);
     _phchIso.push_back(chIso);
     _phnhIso.push_back(nhIso);

     _ph_ele32orig.push_back(RecoHLTMatchingORIG(iEvent,(&*ph)->eta(),(&*ph)->phi(),"hltEle32WPTightGsfTrackIsoFilter") );
     _ph_ele32rehlt.push_back(RecoHLTMatchingHLT2(iEvent,(&*ph)->eta(),(&*ph)->phi(),"hltEle32WPTightGsfTrackIsoFilter") );
     _ph_ele32custom.push_back(RecoHLTMatchingORIG(iEvent,(&*ph)->eta(),(&*ph)->phi(),"hltEle32WPTightGsfTrackIsoRelaxFilter") );
     //_ph_passphoton40customcuts.push_back(RecoHLTMatchingHLT2(iEvent,(&*ph)->eta(),(&*ph)->phi(),"hltEG40CustomEBTightIDTightIsoTrackIsoFilter") );
     _ph_passphoton40origcuts.push_back(RecoHLTMatchingHLT2(iEvent,(&*ph)->eta(),(&*ph)->phi(),"hltEG40EBTightIDTightIsoTrackIsoFilter") );
     _ph_passphoton50origcuts.push_back(RecoHLTMatchingHLT2(iEvent,(&*ph)->eta(),(&*ph)->phi(),"hltEG50EBTightIDTightIsoTrackIsoFilter") );

     _ph_passphoton40customcuts_et40.push_back(RecoHLTMatchingHLT2(iEvent,(&*ph)->eta(),(&*ph)->phi(),"hltEG40CustomEBTightIDTightIsoEtFilter") );
     _ph_passphoton40origcuts_et40.push_back(RecoHLTMatchingHLT2(iEvent,(&*ph)->eta(),(&*ph)->phi(),"hltEG40EBTightIDTightIsoEtFilter") );


   }


   
   }


   
   //Exercise 6.
   //Rerun the HLT_Ele35_WPTight_Gsf and to run on the SingleElectron dataset. 
   //In HLTrigger/Configuration/test do: 
   //cp HLT2_HLT.py HLT2_HLT_SingleEle.py
   //Open HLT2_HLT_SingleEle.py and make the following changes: 
   //The line:
   // process.load('HLTrigger.Configuration.HLT_TutoEffcySession_cff') 
   // should be replaced by: 
   // process.load('HLTrigger.Configuration.HLT_TutoEle35WPTight_cff')
   //The input files should be updated: 
   //fileNames = cms.untracked.vstring('root://cms-xrd-global.cern.ch//store/data/Run2018D/EGamma/MINIAOD/22Jan2019-v2/70001/D8790A22-9BE2-624F-A1CC-6A4A7CAC82D7.root')
   //secondaryFileNames = cms.untracked.vstring(
   //                                         'root://cms-xrd-global.cern.ch//store/data/Run2018D/EGamma/RAW/v1/000/323/755/00000/F9080D12-2CDA-4F43-B7A9-C2F1D05E9C10.root', 
   //                                         'root://cms-xrd-global.cern.ch//store/data/Run2018D/EGamma/RAW/v1/000/323/755/00000/72D435E1-78D4-8047-92BD-3553117A5594.root',                       
   //                                         'root://cms-xrd-global.cern.ch//store/data/Run2018D/EGamma/RAW/v1/000/323/755/00000/266F4E2C-B30A-724E-9183-AD9368A10D51.root' 
   //)     

   //Make the above distributions (e.g. for sietaieta) only for probes passing the triggers and observe that the distributions are indeed truncated at the cut values reported in the HLT config file (HLTrigger/Configuration/python/HLT_TutoEle35WPTight_cff.py





   edm::Handle<double> hltrhoJets;
   iEvent.getByToken(hltFixedGridRhoFastjetAllCaloForMuons_token,hltrhoJets);
   if(hltrhoJets.isValid()  ){
   hlt_rho = *hltrhoJets;
   }
   else hlt_rho = -1;
 
   
   edm::Handle<trigger::TriggerFilterObjectWithRefs> PrevFilterOutput;
   iEvent.getByToken (ele32wptight_l1_Filter_Token_, PrevFilterOutput);
   
   std::vector<edm::Ref<std::vector<reco::RecoEcalCandidate> > > recoCands;
   
   if(PrevFilterOutput.isValid()  ){
     PrevFilterOutput->getObjects(trigger::TriggerCluster, recoCands);
     if(recoCands.empty())PrevFilterOutput->getObjects(trigger::TriggerPhoton, recoCands);
     for (unsigned int i=0; i<recoCands.size(); i++) {
       edm::Ref<std::vector<reco::RecoEcalCandidate> > ref = recoCands[i];
       
       
       float energy = ref->superCluster()->energy();
       float ptphoton = ref->superCluster()->energy() * sin (2*atan(exp(-ref->eta())));
       double etaphoton = ref->eta();
       double phiphoton = ref->phi();

       bool dividebyE = false; bool dividebyEt = false;
       double ele32wptight_sietaieta_HLT = VarStudied(iEvent, etaphoton,phiphoton,ele32wptight_showershape_Var_Token_,ele32wptight_et_Filter_Token_ ,dividebyE, dividebyEt);
       dividebyE = true; dividebyEt = false;
       double ele32wptight_hoe_HLT  = VarStudied(iEvent, etaphoton,phiphoton,ele32wptight_hovere_Var_Token_,ele32wptight_showershape_Filter_Token_ ,dividebyE, dividebyEt);
       //dividebyE = false;  dividebyEt = false;
       //double ele32wptight_r9_HLT  = VarStudied(iEvent, etaphoton,phiphoton,ele32wptight_r9_Var_Token_,ele32wptight_hoe_Filter_Token_ ,dividebyE, dividebyEt);
       dividebyE =false; dividebyEt = true;
       double ele32wptight_ecaliso_HLT  = VarStudied(iEvent, etaphoton,phiphoton,ele32wptight_ecaliso_Var_Token_,ele32wptight_hoe_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_hcaliso_HLT  = VarStudied(iEvent, etaphoton,phiphoton,ele32wptight_hcaliso_Var_Token_,ele32wptight_ecaliso_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_trackiso_HLT  = VarStudied(iEvent, etaphoton,phiphoton,ele32wptight_trackiso_Var_Token_,ele32wptight_hcaliso_Filter_Token_ ,dividebyE, dividebyEt); 

       dividebyE = false;  dividebyEt = false;


       double ele32wptight_pixelmatch_HLT  =  PixelMatchVariable(iEvent, etaphoton,phiphoton,ele32wptight_hcaliso_Filter_Token_);
       //double ele32wptight_pixelmatch_HLT  = VarStudied(iEvent, etaphoton,phiphoton,ele32wptight_pixelmatch_Var_Token_,ele32wptight_hcaliso_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_pms2_HLT  = VarStudied(iEvent, etaphoton,phiphoton,ele32wptight_pms2_Var_Token_,ele32wptight_pixelmatch_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_ooeminoop_HLT  = VarStudied(iEvent, etaphoton,phiphoton,ele32wptight_ooeminoop_Var_Token_,ele32wptight_pms2_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_missinghits_HLT  = VarStudied(iEvent, etaphoton,phiphoton,ele32wptight_missinghits_Var_Token_,ele32wptight_ooeminoop_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_deta_HLT  = VarStudied(iEvent, etaphoton,phiphoton,ele32wptight_deta_Var_Token_,ele32wptight_missinghits_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_dphi_HLT  = VarStudied(iEvent, etaphoton,phiphoton,ele32wptight_dphi_Var_Token_,ele32wptight_deta_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_gsfcharge_HLT  = VarStudied(iEvent, etaphoton,phiphoton,ele32wptight_gsfcharge_Var_Token_,ele32wptight_deta_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_gsfpt_HLT  = VarStudied(iEvent, etaphoton,phiphoton,ele32wptight_gsfpt_Var_Token_,ele32wptight_deta_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_gsfeta_HLT  = VarStudied(iEvent, etaphoton,phiphoton,ele32wptight_gsfeta_Var_Token_,ele32wptight_deta_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_gsfphi_HLT  = VarStudied(iEvent, etaphoton,phiphoton,ele32wptight_gsfphi_Var_Token_,ele32wptight_deta_Filter_Token_ ,dividebyE, dividebyEt);

       dividebyE =false; dividebyEt = true;
       double ele32wptight_customtrackiso_HLT  = VarStudied(iEvent, etaphoton,phiphoton,ele32wptight_customtrackiso_Var_Token_,ele32wptight_hcaliso_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_custom1trackiso_HLT  = VarStudied(iEvent, etaphoton,phiphoton,ele32wptight_custom1trackiso_Var_Token_,ele32wptight_hcaliso_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_custom2trackiso_HLT  = VarStudied(iEvent, etaphoton,phiphoton,ele32wptight_custom2trackiso_Var_Token_,ele32wptight_hcaliso_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_custom3trackiso_HLT  = VarStudied(iEvent, etaphoton,phiphoton,ele32wptight_custom3trackiso_Var_Token_,ele32wptight_hcaliso_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_custom4trackiso_HLT  = VarStudied(iEvent, etaphoton,phiphoton,ele32wptight_custom4trackiso_Var_Token_,ele32wptight_hcaliso_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_custom5trackiso_HLT  = VarStudied(iEvent, etaphoton,phiphoton,ele32wptight_custom5trackiso_Var_Token_,ele32wptight_hcaliso_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_custom6trackiso_HLT  = VarStudied(iEvent, etaphoton,phiphoton,ele32wptight_custom6trackiso_Var_Token_,ele32wptight_hcaliso_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_custom7trackiso_HLT  = VarStudied(iEvent, etaphoton,phiphoton,ele32wptight_custom7trackiso_Var_Token_,ele32wptight_hcaliso_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_customecaliso_HLT  = VarStudied(iEvent, etaphoton,phiphoton,ele32wptight_customecaliso_Var_Token_,ele32wptight_hoe_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_customecaliso2_HLT  = VarStudied(iEvent, etaphoton,phiphoton,ele32wptight_customecaliso2_Var_Token_,ele32wptight_hoe_Filter_Token_ ,dividebyE, dividebyEt);
       double ele32wptight_customhcaliso_HLT  = VarStudied(iEvent, etaphoton,phiphoton,ele32wptight_customhcaliso_Var_Token_,ele32wptight_ecaliso_Filter_Token_ ,dividebyE, dividebyEt);
       
       
       hltphoton_pt.push_back(ptphoton);
       hltphoton_eta.push_back(etaphoton);
       hltphoton_phi.push_back(phiphoton);
       
       hltphoton_ele32wptight_sietaieta_HLT.push_back(ele32wptight_sietaieta_HLT);
       hltphoton_ele32wptight_hoe_HLT.push_back(ele32wptight_hoe_HLT);
       //hltphoton_ele32wptight_r9_HLT.push_back(ele32wptight_r9_HLT);
       hltphoton_ele32wptight_ecaliso_HLT.push_back(ele32wptight_ecaliso_HLT);
       hltphoton_ele32wptight_hcaliso_HLT.push_back(ele32wptight_hcaliso_HLT);
       hltphoton_ele32wptight_pixelmatch_HLT.push_back(ele32wptight_pixelmatch_HLT);
       hltphoton_ele32wptight_pms2_HLT.push_back(ele32wptight_pms2_HLT);
       hltphoton_ele32wptight_ooeminoop_HLT.push_back(ele32wptight_ooeminoop_HLT);
       hltphoton_ele32wptight_missinghits_HLT.push_back(ele32wptight_missinghits_HLT);
       hltphoton_ele32wptight_deta_HLT.push_back(ele32wptight_deta_HLT);
       hltphoton_ele32wptight_dphi_HLT.push_back(ele32wptight_dphi_HLT);

       hltphoton_ele32wptight_gsfcharge_HLT.push_back(ele32wptight_gsfcharge_HLT);
       hltphoton_ele32wptight_gsfpt_HLT.push_back(ele32wptight_gsfpt_HLT);
       hltphoton_ele32wptight_gsfeta_HLT.push_back(ele32wptight_gsfeta_HLT);
       hltphoton_ele32wptight_gsfphi_HLT.push_back(ele32wptight_gsfphi_HLT);

       hltphoton_ele32wptight_trackiso_HLT.push_back(ele32wptight_trackiso_HLT);
       hltphoton_ele32wptight_customtrackiso_HLT.push_back(ele32wptight_customtrackiso_HLT);
       hltphoton_ele32wptight_custom1trackiso_HLT.push_back(ele32wptight_custom1trackiso_HLT);
       hltphoton_ele32wptight_custom2trackiso_HLT.push_back(ele32wptight_custom2trackiso_HLT);
       hltphoton_ele32wptight_custom3trackiso_HLT.push_back(ele32wptight_custom3trackiso_HLT);
       hltphoton_ele32wptight_custom4trackiso_HLT.push_back(ele32wptight_custom4trackiso_HLT);
       hltphoton_ele32wptight_custom5trackiso_HLT.push_back(ele32wptight_custom5trackiso_HLT);
       hltphoton_ele32wptight_custom6trackiso_HLT.push_back(ele32wptight_custom6trackiso_HLT);
       hltphoton_ele32wptight_custom7trackiso_HLT.push_back(ele32wptight_custom7trackiso_HLT);
       hltphoton_ele32wptight_customecaliso_HLT.push_back(ele32wptight_customecaliso_HLT);
       hltphoton_ele32wptight_customecaliso2_HLT.push_back(ele32wptight_customecaliso2_HLT);
       hltphoton_ele32wptight_customhcaliso_HLT.push_back(ele32wptight_customhcaliso_HLT);
       

       
       
     }
   }
     /*
   bool dividebyE = false; bool dividebyEt = false;
   photon_ele32wptight_sietaieta_HLT = VarHLT(iEvent,ele32wptight_showershape_Var_Token_,ele32wptight_et_Filter_Token_ ,dividebyE, dividebyEt);
   dividebyE = true; dividebyEt = false;
   photon_ele32wptight_hoe_HLT  = VarHLT(iEvent,ele32wptight_hovere_Var_Token_,ele32wptight_showershape_Filter_Token_ ,dividebyE, dividebyEt);
   dividebyE = false;  dividebyEt = false;
   photon_ele32wptight_r9_HLT  = VarHLT(iEvent,ele32wptight_r9_Var_Token_,ele32wptight_hoe_Filter_Token_ ,dividebyE, dividebyEt);
   dividebyE =false; dividebyEt = true;
   photon_ele32wptight_ecaliso_HLT  = VarHLT(iEvent,ele32wptight_ecaliso_Var_Token_,ele32wptight_r9_Filter_Token_ ,dividebyE, dividebyEt);
   photon_ele32wptight_hcaliso_HLT  = VarHLT(iEvent,ele32wptight_hcaliso_Var_Token_,ele32wptight_ecaliso_Filter_Token_ ,dividebyE, dividebyEt);
   photon_ele32wptight_trackiso_HLT  = VarHLT(iEvent,ele32wptight_trackiso_Var_Token_,ele32wptight_hcaliso_Filter_Token_ ,dividebyE, dividebyEt);
     */
   
  
   /*if(
      (useMINIAOD and probe_ele_pt.size()>0)
      or (!useMINIAOD and (hltphoton_pt.size()>0 or HLT_Ele32_WPTight_Gsf_ORIG or HLT_DoubleMu3_DCA_PFMET50_PFMHT60_Mass0p1 or HLT_DoubleMu3_DZ_PFMET50_PFMHT60 or HLT_DoubleMu3_DCA_PFMET50_PFMHT60))
      ){
     outputTree->Fill();
       }
   */

   //   if(!TheGenParticles.isValid()|| lhe_dielemass>0) outputTree->Fill();
    outputTree->Fill();

   probe_ele_pt.clear();
   probe_ele_eta.clear();
   probe_ele_phi.clear();
   probe_ele_mll.clear();
   probe_ele_ele32wptight_pt_HLT.clear();
   probe_ele_ele32wptight_sietaieta_HLT.clear();
   probe_ele_ele32wptight_hoe_HLT.clear();
   //   probe_ele_ele32wptight_r9_HLT.clear();
   probe_ele_ele32wptight_ecaliso_HLT.clear();
   probe_ele_ele32wptight_hcaliso_HLT.clear();
   probe_ele_ele32wptight_pixelmatch_HLT.clear();
   probe_ele_ele32wptight_pms2_HLT.clear();
   probe_ele_ele32wptight_ooeminoop_HLT.clear();
   probe_ele_ele32wptight_missinghits_HLT.clear();
   probe_ele_ele32wptight_deta_HLT.clear();
   probe_ele_ele32wptight_dphi_HLT.clear();
   probe_ele_ele32wptight_trackiso_HLT.clear();
   probe_ele_ele32wptightorig_trackiso_HLT.clear();
   probe_ele_ele32wptight_customtrackiso_HLT.clear();
   probe_ele_ele32wptight_custom1trackiso_HLT.clear();
   probe_ele_ele32wptight_custom2trackiso_HLT.clear();
   probe_ele_ele32wptight_custom3trackiso_HLT.clear();
   probe_ele_ele32wptight_custom4trackiso_HLT.clear();
   probe_ele_ele32wptight_custom5trackiso_HLT.clear();
   probe_ele_ele32wptight_custom6trackiso_HLT.clear();
   probe_ele_ele32wptight_custom7trackiso_HLT.clear();
   probe_ele_ele32wptight_customecaliso_HLT.clear();
   probe_ele_ele32wptight_customecaliso2_HLT.clear();
   probe_ele_ele32wptight_customhcaliso_HLT.clear();


   probe_ele_ele32orig.clear();
   probe_ele_ele32rehlt.clear();
   probe_ele_ele30orig.clear();
   probe_ele_ele30rehlt.clear();
   probe_ele_ele30customrehlt.clear();

   probe_ele_ele12orig.clear();
   probe_ele_ele12orig_l1eg12.clear();
   probe_ele_ele12rehlt.clear();

   probe_ele_ele32custom.clear();
   //   probe_ele_passphoton40customcuts.clear();
   probe_ele_passphoton40origcuts.clear();
   probe_ele_passphoton50origcuts.clear();
   probe_ele_passphoton40customcuts_et40.clear();
   probe_ele_passphoton40origcuts_et40.clear();
   probe_ele_ele32wptight_gsfcharge_HLT.clear();
   probe_ele_ele32wptight_gsfpt_HLT.clear();
   probe_ele_ele32wptight_gsfeta_HLT.clear();
   probe_ele_ele32wptight_gsfphi_HLT.clear();



   hltphoton_pt.clear();
   hltphoton_eta.clear();
   hltphoton_phi.clear();
   
   hltphoton_ele32wptight_sietaieta_HLT.clear();
   hltphoton_ele32wptight_hoe_HLT.clear();
   //   hltphoton_ele32wptight_r9_HLT.clear();
   hltphoton_ele32wptight_ecaliso_HLT.clear();
   hltphoton_ele32wptight_hcaliso_HLT.clear();
   hltphoton_ele32wptight_pixelmatch_HLT.clear();
   hltphoton_ele32wptight_pms2_HLT.clear();
   hltphoton_ele32wptight_ooeminoop_HLT.clear();
   hltphoton_ele32wptight_missinghits_HLT.clear();
   hltphoton_ele32wptight_deta_HLT.clear();
   hltphoton_ele32wptight_dphi_HLT.clear();

   hltphoton_ele32wptight_gsfcharge_HLT.clear();
   hltphoton_ele32wptight_gsfpt_HLT.clear();
   hltphoton_ele32wptight_gsfeta_HLT.clear();
   hltphoton_ele32wptight_gsfphi_HLT.clear();

   hltphoton_ele32wptight_trackiso_HLT.clear();
   hltphoton_ele32wptight_customtrackiso_HLT.clear();
   hltphoton_ele32wptight_custom1trackiso_HLT.clear();
   hltphoton_ele32wptight_custom2trackiso_HLT.clear();
   hltphoton_ele32wptight_custom3trackiso_HLT.clear();
   hltphoton_ele32wptight_custom4trackiso_HLT.clear();
   hltphoton_ele32wptight_custom5trackiso_HLT.clear();
   hltphoton_ele32wptight_custom6trackiso_HLT.clear();
   hltphoton_ele32wptight_custom7trackiso_HLT.clear();
   hltphoton_ele32wptight_customecaliso_HLT.clear();
   hltphoton_ele32wptight_customecaliso2_HLT.clear();
   hltphoton_ele32wptight_customhcaliso_HLT.clear();

   _phEta.clear();
   _phPhi.clear();
   _phPt.clear();
   _phPassTightID.clear();
   _phPassLooseID.clear();
   _phgIso.clear();
   _phchIso.clear();
   _phnhIso.clear();

   _ph_ele32orig.clear();
   _ph_ele32rehlt.clear();
   _ph_ele32custom.clear();
   //_ph_passphoton40customcuts.clear();
   _ph_passphoton40origcuts.clear();
   _ph_passphoton50origcuts.clear();
   _ph_passphoton40customcuts_et40.clear();
   _ph_passphoton40origcuts_et40.clear();
   

   _L1eg_pt.clear();
   _L1eg_eta.clear();
   _L1eg_phi.clear();
   _L1eg_bx.clear();
   _L1eg_iso.clear();


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
  outputTree->Branch("lhe_dielemass",&lhe_dielemass,"lhe_dielemass/F");
  outputTree->Branch("fromWZdecay",&fromWZdecay,"fromWZdecay/O");
  outputTree->Branch("lhe_dielept",&lhe_dielept,"lhe_dielept/F");
  outputTree->Branch("lhe_dieleeta",&lhe_dieleeta,"lhe_dieleeta/F");
  outputTree->Branch("lhe_dielephi",&lhe_dielephi,"lhe_dielephi/F");
  outputTree->Branch("lhe_dieledeta",&lhe_dieledeta,"lhe_dieledeta/F");
  outputTree->Branch("lhe_dieledphi",&lhe_dieledphi,"lhe_dieledphi/F");
 
  outputTree->Branch("HLT_Ele32_WPTight_Gsf",&HLT_Ele32_WPTight_Gsf,"HLT_Ele32_WPTight_Gsf/O");
  outputTree->Branch("HLT_Ele32_WPTight_Gsf_Relax",&HLT_Ele32_WPTight_Gsf_Relax,"HLT_Ele32_WPTight_Gsf_Relax/O");
  outputTree->Branch("HLT_IsoMu24",&HLT_IsoMu24,"HLT_IsoMu24/O");
  outputTree->Branch("HLT_Diphoton15_10_TightID_ECALTrackIsoDr0p2_EBEB",&HLT_Diphoton15_10_TightID_ECALTrackIsoDr0p2_EBEB,"HLT_Diphoton15_10_TightID_ECALTrackIsoDr0p2_EBEB/O");
  outputTree->Branch("HLT_Diphoton15_10_TightID_ECALTrackIsoDr0p2to0p4_EBEB",&HLT_Diphoton15_10_TightID_ECALTrackIsoDr0p2to0p4_EBEB,"HLT_Diphoton15_10_TightID_ECALTrackIsoDr0p2to0p4_EBEB/O");
  outputTree->Branch("HLT_DoubleEle15_5_CaloIdL_MW",&HLT_DoubleEle15_5_CaloIdL_MW,"HLT_DoubleEle15_5_CaloIdL_MW/O");
  outputTree->Branch("HLT_DoubleEle25_CaloIdL_MW",&HLT_DoubleEle25_CaloIdL_MW,"HLT_DoubleEle25_CaloIdL_MW/O");
  outputTree->Branch("HLT_DoubleEle6p5_eta1p22_mMax6",&HLT_DoubleEle6p5_eta1p22_mMax6,"HLT_DoubleEle6p5_eta1p22_mMax6/O");
  outputTree->Branch("HLT_Photon30EB_TightID_TightIso",&HLT_Photon30EB_TightID_TightIso,"HLT_Photon30EB_TightID_TightIso/O");
  outputTree->Branch("HLT_Photon40EB_TightID_TightIso",&HLT_Photon40EB_TightID_TightIso,"HLT_Photon40EB_TightID_TightIso/O");
  outputTree->Branch("HLT_Photon40EB_TightID_TightIso_Custom",&HLT_Photon40EB_TightID_TightIso_Custom,"HLT_Photon40EB_TightID_TightIso_Custom/O");
  outputTree->Branch("HLT_Photon40EB_CustomTightID_TightIso",&HLT_Photon40EB_CustomTightID_TightIso,"HLT_Photon40EB_CustomTightID_TightIso/O");
  outputTree->Branch("HLT_Photon40EB_DisabledTightID_TightIso",&HLT_Photon40EB_DisabledTightID_TightIso,"HLT_Photon40EB_DisabledTightID_TightIso/O");
  outputTree->Branch("HLT_Photon50EB_TightID_TightIso",&HLT_Photon50EB_TightID_TightIso,"HLT_Photon50EB_TightID_TightIso/O");
  outputTree->Branch("HLT_Photon55EB_TightID_TightIso",&HLT_Photon55EB_TightID_TightIso,"HLT_Photon55EB_TightID_TightIso/O");
  outputTree->Branch("HLT_Photon75EB_TightID_TightIso",&HLT_Photon75EB_TightID_TightIso,"HLT_Photon75EB_TightID_TightIso/O");
  outputTree->Branch("HLT_Photon90EB_TightID_TightIso",&HLT_Photon90EB_TightID_TightIso,"HLT_Photon90EB_TightID_TightIso/O");
  outputTree->Branch("HLT_Photon110EB_TightID_TightIso",&HLT_Photon110EB_TightID_TightIso,"HLT_Photon110EB_TightID_TightIso/O");
  outputTree->Branch("HLT_DoubleMu3_DCA_PFMET50_PFMHT60",&HLT_DoubleMu3_DCA_PFMET50_PFMHT60,"HLT_DoubleMu3_DCA_PFMET50_PFMHT60/O");
  outputTree->Branch("HLT_DoubleMu3_DZ_PFMET50_PFMHT60",&HLT_DoubleMu3_DZ_PFMET50_PFMHT60,"HLT_DoubleMu3_DZ_PFMET50_PFMHT60/O");
  outputTree->Branch("HLT_DoubleMu3_DCA_PFMET50_PFMHT60_Mass0p1",&HLT_DoubleMu3_DCA_PFMET50_PFMHT60_Mass0p1,"HLT_DoubleMu3_DCA_PFMET50_PFMHT60_Mass0p1/O");
  outputTree->Branch("HLT_DoubleMu3_DCA_PFMET50_PFMHT60_Mass2p0",&HLT_DoubleMu3_DCA_PFMET50_PFMHT60_Mass2p0,"HLT_DoubleMu3_DCA_PFMET50_PFMHT60_Mass2p0/O");
  outputTree->Branch("HLT_DoubleMu3_DCA_PFMET50_PFMHT60_Mass2p0_noDCA",&HLT_DoubleMu3_DCA_PFMET50_PFMHT60_Mass2p0_noDCA,"HLT_DoubleMu3_DCA_PFMET50_PFMHT60_Mass2p0_noDCA/O");
  outputTree->Branch("HLT_Mu50_ORIG",&HLT_Mu50_ORIG,"HLT_Mu50_ORIG/O");
  outputTree->Branch("HLT_Ele32_WPTight_Gsf_ORIG",&HLT_Ele32_WPTight_Gsf_ORIG,"HLT_Ele32_WPTight_Gsf_ORIG/O");
  outputTree->Branch("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_ORIG",&HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_ORIG,"HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_ORIG/O");
  outputTree->Branch("HLT_DoubleEle25_CaloIdL_MW_ORIG",&HLT_DoubleEle25_CaloIdL_MW_ORIG,"HLT_DoubleEle25_CaloIdL_MW_ORIG/O");
  outputTree->Branch("HLT_DoubleEle6p5_eta1p22_mMax6_ORIG",&HLT_DoubleEle6p5_eta1p22_mMax6_ORIG,"HLT_DoubleEle6p5_eta1p22_mMax6_ORIG/O");
  outputTree->Branch("HLT_Photon45EB_TightID_TightIso_ORIG",&HLT_Photon45EB_TightID_TightIso_ORIG,"HLT_Photon45EB_TightID_TightIso_ORIG/O");
  outputTree->Branch("HLT_IsoMu24_ORIG",&HLT_IsoMu24_ORIG,"HLT_IsoMu24_ORIG/O");
  outputTree->Branch("HLT_DoubleMu3_DCA_PFMET50_PFMHT60_ORIG",&HLT_DoubleMu3_DCA_PFMET50_PFMHT60_ORIG,"HLT_DoubleMu3_DCA_PFMET50_PFMHT60_ORIG/O");
  outputTree->Branch("HLT_Photon30EB_TightID_TightIso_ORIG",&HLT_Photon30EB_TightID_TightIso_ORIG,"HLT_Photon30EB_TightID_TightIso_ORIG/O");
  outputTree->Branch("HLT_Photon50EB_TightID_TightIso_ORIG",&HLT_Photon50EB_TightID_TightIso_ORIG,"HLT_Photon50EB_TightID_TightIso_ORIG/O");

  outputTree->Branch("HLT_Photon75EB_TightID_TightIso_ORIG",&HLT_Photon75EB_TightID_TightIso_ORIG,"HLT_Photon75EB_TightID_TightIso_ORIG/O");
  outputTree->Branch("HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL_PFHT380_ORIG",&HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL_PFHT380_ORIG,"HLT_Photon60_R9Id90_CaloIdL_IsoL_DisplacedIdL_PFHT380_ORIG/O");
  outputTree->Branch("HLT_Photon32_OneProng32_M50To105_ORIG",&HLT_Photon32_OneProng32_M50To105_ORIG,"HLT_Photon32_OneProng32_M50To105_ORIG/O");
  outputTree->Branch("HLT_Photon60_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3_ORIG",&HLT_Photon60_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3_ORIG,"HLT_Photon60_R9Id90_HE10_IsoM_EBOnly_PFJetsMJJ300DEta3_ORIG/O");
  outputTree->Branch("HLT_Photon35_TwoProngs35_ORIG",&HLT_Photon35_TwoProngs35_ORIG,"HLT_Photon35_TwoProngs35_ORIG/O");
  outputTree->Branch("HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_ORIG",&HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_ORIG,"HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ_Mass3p8_ORIG/O");
  outputTree->Branch("HLT_Photon90EB_TightID_TightIso_ORIG",&HLT_Photon90EB_TightID_TightIso_ORIG,"HLT_Photon90EB_TightID_TightIso_ORIG/O");
  outputTree->Branch("HLT_Diphoton30_18_R9IdL_AND_HE_AND_IsoCaloId_ORIG",&HLT_Diphoton30_18_R9IdL_AND_HE_AND_IsoCaloId_ORIG,"HLT_Diphoton30_18_R9IdL_AND_HE_AND_IsoCaloId_ORIG/O");
  outputTree->Branch("HLT_Diphoton22_14_eta1p5_R9IdL_AND_HET_AND_IsoTCaloIdT_ORIG",&HLT_Diphoton22_14_eta1p5_R9IdL_AND_HET_AND_IsoTCaloIdT_ORIG,"HLT_Diphoton22_14_eta1p5_R9IdL_AND_HET_AND_IsoTCaloIdT_ORIG/O");
  outputTree->Branch("HLT_Diphoton30_22_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass90_ORIG",&HLT_Diphoton30_22_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass90_ORIG,"HLT_Diphoton30_22_R9Id_OR_IsoCaloId_AND_HE_R9Id_Mass90_ORIG/O");

  outputTree->Branch("HLT_Photon110EB_TightID_TightIso_ORIG",&HLT_Photon110EB_TightID_TightIso_ORIG,"HLT_Photon110EB_TightID_TightIso_ORIG/O");
  outputTree->Branch("HLT_Photon33_ORIG",&HLT_Photon33_ORIG,"HLT_Photon33_ORIG/O");
  outputTree->Branch("HLT_Photon50_ORIG",&HLT_Photon50_ORIG,"HLT_Photon50_ORIG/O");
  outputTree->Branch("passl1singleordieg",&passl1singleordieg,"passl1singleordieg/O");

  
  outputTree->Branch("probe_ele_pt",&probe_ele_pt);
  outputTree->Branch("probe_ele_eta",&probe_ele_eta);
  outputTree->Branch("probe_ele_phi",&probe_ele_phi);
  outputTree->Branch("probe_ele_mll",&probe_ele_mll);
  outputTree->Branch("probe_ele_ele32wptight_pt_HLT",&probe_ele_ele32wptight_pt_HLT);
  outputTree->Branch("probe_ele_ele32wptight_sietaieta_HLT",&probe_ele_ele32wptight_sietaieta_HLT);
  outputTree->Branch("probe_ele_ele32wptight_hoe_HLT",&probe_ele_ele32wptight_hoe_HLT);
  //outputTree->Branch("probe_ele_ele32wptight_r9_HLT",&probe_ele_ele32wptight_r9_HLT);
  outputTree->Branch("probe_ele_ele32wptight_ecaliso_HLT",&probe_ele_ele32wptight_ecaliso_HLT);
  outputTree->Branch("probe_ele_ele32wptight_hcaliso_HLT",&probe_ele_ele32wptight_hcaliso_HLT);
  outputTree->Branch("probe_ele_ele32wptight_pixelmatch_HLT",&probe_ele_ele32wptight_pixelmatch_HLT);
  outputTree->Branch("probe_ele_ele32wptight_pms2_HLT",&probe_ele_ele32wptight_pms2_HLT);
  outputTree->Branch("probe_ele_ele32wptight_ooeminoop_HLT",&probe_ele_ele32wptight_ooeminoop_HLT);
  outputTree->Branch("probe_ele_ele32wptight_missinghits_HLT",&probe_ele_ele32wptight_missinghits_HLT);
  outputTree->Branch("probe_ele_ele32wptight_deta_HLT",&probe_ele_ele32wptight_deta_HLT);
  outputTree->Branch("probe_ele_ele32wptight_dphi_HLT",&probe_ele_ele32wptight_dphi_HLT); 
  outputTree->Branch("probe_ele_ele32wptight_trackiso_HLT",&probe_ele_ele32wptight_trackiso_HLT);
  outputTree->Branch("probe_ele_ele32wptightorig_trackiso_HLT",&probe_ele_ele32wptightorig_trackiso_HLT);
  outputTree->Branch("probe_ele_ele32wptight_customtrackiso_HLT",&probe_ele_ele32wptight_customtrackiso_HLT);
  outputTree->Branch("probe_ele_ele32wptight_custom1trackiso_HLT",&probe_ele_ele32wptight_custom1trackiso_HLT);
  outputTree->Branch("probe_ele_ele32wptight_custom2trackiso_HLT",&probe_ele_ele32wptight_custom2trackiso_HLT);
  /*outputTree->Branch("probe_ele_ele32wptight_custom3trackiso_HLT",&probe_ele_ele32wptight_custom3trackiso_HLT);
  outputTree->Branch("probe_ele_ele32wptight_custom4trackiso_HLT",&probe_ele_ele32wptight_custom4trackiso_HLT);
  outputTree->Branch("probe_ele_ele32wptight_custom5trackiso_HLT",&probe_ele_ele32wptight_custom5trackiso_HLT);
  outputTree->Branch("probe_ele_ele32wptight_custom6trackiso_HLT",&probe_ele_ele32wptight_custom6trackiso_HLT);
  outputTree->Branch("probe_ele_ele32wptight_custom7trackiso_HLT",&probe_ele_ele32wptight_custom7trackiso_HLT);

  outputTree->Branch("probe_ele_ele32wptight_customhcaliso_HLT",&probe_ele_ele32wptight_customhcaliso_HLT);*/
  outputTree->Branch("probe_ele_ele32wptight_customecaliso_HLT",&probe_ele_ele32wptight_customecaliso_HLT);
  outputTree->Branch("probe_ele_ele32wptight_customecaliso2_HLT",&probe_ele_ele32wptight_customecaliso2_HLT);
  outputTree->Branch("probe_ele_ele12orig",&probe_ele_ele12orig);
  outputTree->Branch("probe_ele_ele12orig_l1eg12",&probe_ele_ele12orig_l1eg12);
  outputTree->Branch("probe_ele_ele12rehlt",&probe_ele_ele12rehlt);
  outputTree->Branch("probe_ele_ele32orig",&probe_ele_ele32orig);
  outputTree->Branch("probe_ele_ele32rehlt",&probe_ele_ele32rehlt);

  outputTree->Branch("probe_ele_ele30orig",&probe_ele_ele30orig);
  outputTree->Branch("probe_ele_ele30rehlt",&probe_ele_ele30rehlt);
  outputTree->Branch("probe_ele_ele30customrehlt",&probe_ele_ele30customrehlt);


  outputTree->Branch("probe_ele_ele32custom",&probe_ele_ele32custom);
  outputTree->Branch("probe_ele_passphoton40origcuts",&probe_ele_passphoton40origcuts);
  outputTree->Branch("probe_ele_passphoton50origcuts",&probe_ele_passphoton50origcuts);
  outputTree->Branch("probe_ele_passphoton40customcuts_et40",&probe_ele_passphoton40customcuts_et40);
  outputTree->Branch("probe_ele_passphoton40origcuts_et40",&probe_ele_passphoton40origcuts_et40);

  outputTree->Branch("probe_ele_ele32wptight_gsfcharge_HLT",&probe_ele_ele32wptight_gsfcharge_HLT); 
  outputTree->Branch("probe_ele_ele32wptight_gsfpt_HLT",&probe_ele_ele32wptight_gsfpt_HLT); 
  outputTree->Branch("probe_ele_ele32wptight_gsfeta_HLT",&probe_ele_ele32wptight_gsfeta_HLT); 
  outputTree->Branch("probe_ele_ele32wptight_gsfphi_HLT",&probe_ele_ele32wptight_gsfphi_HLT); 


  outputTree->Branch("hltphoton_pt",&hltphoton_pt);
  outputTree->Branch("hltphoton_eta",&hltphoton_eta);
  outputTree->Branch("hltphoton_phi",&hltphoton_phi);
  outputTree->Branch("hltphoton_ele32wptight_sietaieta_HLT",&hltphoton_ele32wptight_sietaieta_HLT);
  outputTree->Branch("hltphoton_ele32wptight_hoe_HLT",&hltphoton_ele32wptight_hoe_HLT);
  //outputTree->Branch("hltphoton_ele32wptight_r9_HLT",&hltphoton_ele32wptight_r9_HLT);
  outputTree->Branch("hltphoton_ele32wptight_ecaliso_HLT",&hltphoton_ele32wptight_ecaliso_HLT);
  outputTree->Branch("hltphoton_ele32wptight_hcaliso_HLT",&hltphoton_ele32wptight_hcaliso_HLT);
  outputTree->Branch("hltphoton_ele32wptight_pixelmatch_HLT",&hltphoton_ele32wptight_pixelmatch_HLT);
  outputTree->Branch("hltphoton_ele32wptight_pms2_HLT",&hltphoton_ele32wptight_pms2_HLT);
  outputTree->Branch("hltphoton_ele32wptight_ooeminoop_HLT",&hltphoton_ele32wptight_ooeminoop_HLT);
  outputTree->Branch("hltphoton_ele32wptight_missinghits_HLT",&hltphoton_ele32wptight_missinghits_HLT);
  outputTree->Branch("hltphoton_ele32wptight_deta_HLT",&hltphoton_ele32wptight_deta_HLT);
  outputTree->Branch("hltphoton_ele32wptight_dphi_HLT",&hltphoton_ele32wptight_dphi_HLT); 
  outputTree->Branch("hltphoton_ele32wptight_gsfcharge_HLT",&hltphoton_ele32wptight_gsfcharge_HLT); 
  outputTree->Branch("hltphoton_ele32wptight_gsfpt_HLT",&hltphoton_ele32wptight_gsfpt_HLT); 
  outputTree->Branch("hltphoton_ele32wptight_gsfeta_HLT",&hltphoton_ele32wptight_gsfeta_HLT); 
  outputTree->Branch("hltphoton_ele32wptight_gsfphi_HLT",&hltphoton_ele32wptight_gsfphi_HLT); 
  outputTree->Branch("hltphoton_ele32wptight_trackiso_HLT",&hltphoton_ele32wptight_trackiso_HLT);

  outputTree->Branch("hltphoton_ele32wptight_customecaliso_HLT",&hltphoton_ele32wptight_customecaliso_HLT);
  outputTree->Branch("hltphoton_ele32wptight_customecaliso2_HLT",&hltphoton_ele32wptight_customecaliso2_HLT);
  outputTree->Branch("hltphoton_ele32wptight_customtrackiso_HLT",&hltphoton_ele32wptight_customtrackiso_HLT);
  outputTree->Branch("hltphoton_ele32wptight_custom1trackiso_HLT",&hltphoton_ele32wptight_custom1trackiso_HLT);
  outputTree->Branch("hltphoton_ele32wptight_custom2trackiso_HLT",&hltphoton_ele32wptight_custom2trackiso_HLT);
  /*outputTree->Branch("hltphoton_ele32wptight_custom3trackiso_HLT",&hltphoton_ele32wptight_custom3trackiso_HLT);
  outputTree->Branch("hltphoton_ele32wptight_custom4trackiso_HLT",&hltphoton_ele32wptight_custom4trackiso_HLT);
  outputTree->Branch("hltphoton_ele32wptight_custom5trackiso_HLT",&hltphoton_ele32wptight_custom5trackiso_HLT);
  outputTree->Branch("hltphoton_ele32wptight_custom6trackiso_HLT",&hltphoton_ele32wptight_custom6trackiso_HLT);
  outputTree->Branch("hltphoton_ele32wptight_custom7trackiso_HLT",&hltphoton_ele32wptight_custom7trackiso_HLT);

  outputTree->Branch("hltphoton_ele32wptight_customhcaliso_HLT",&hltphoton_ele32wptight_customhcaliso_HLT);
  */

  outputTree->Branch("_phEta",&_phEta);
  outputTree->Branch("_phPhi",&_phPhi);
  outputTree->Branch("_phPt",&_phPt);
  outputTree->Branch("_phPassTightID",&_phPassTightID);
  outputTree->Branch("_phPassLooseID",&_phPassLooseID);
  outputTree->Branch("_phgIso",&_phgIso);
  outputTree->Branch("_phchIso",&_phchIso);
  outputTree->Branch("_phnhIso",&_phnhIso);
  outputTree->Branch("_ph_ele32orig",&_ph_ele32orig);
  outputTree->Branch("_ph_ele32rehlt",&_ph_ele32rehlt);
  outputTree->Branch("_ph_ele32custom",&_ph_ele32custom);
  outputTree->Branch("_ph_passphoton40origcuts",&_ph_passphoton40origcuts);
  outputTree->Branch("_ph_passphoton50origcuts",&_ph_passphoton50origcuts);
  outputTree->Branch("_ph_passphoton40customcuts_et40",&_ph_passphoton40customcuts_et40);
  outputTree->Branch("_ph_passphoton40origcuts_et40",&_ph_passphoton40origcuts_et40);

  
  outputTree->Branch("_L1eg_pt",&_L1eg_pt);
  outputTree->Branch("_L1eg_eta",&_L1eg_eta);
  outputTree->Branch("_L1eg_phi",&_L1eg_phi);
  outputTree->Branch("_L1eg_bx",&_L1eg_bx);
  outputTree->Branch("_L1eg_iso",&_L1eg_iso);
    

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

bool TriggerAnalyzerRAWMiniAOD::PassOfflineMuonSelection(const pat::Muon *mu, reco::Vertex::Point PV){
  if ( !(mu->isGlobalMuon() || mu->isTrackerMuon() )) return false;
  if ( !(mu->isPFMuon()) ) return false;
  const reco::TrackRef innerTrack = mu->innerTrack();
  if( innerTrack.isNull() )return false;
  
  bool goodGlb =  mu->isGlobalMuon() &&  mu->globalTrack()->normalizedChi2() < 3
    &&  mu->combinedQuality().chi2LocalPosition < 12  && mu->combinedQuality().trkKink < 20;
  bool good =  mu->innerTrack()->validFraction() >= 0.8 &&  mu->segmentCompatibility() >= (goodGlb ? 0.303 : 0.451)  ;
  
  if(!good) return false;
  if(TMath::Abs(innerTrack->dxy(PV)) >0.1 ) return false;
  if(TMath::Abs(innerTrack->dz(PV)) >0.1 ) return false;  
  
  double chargedHadronIso = mu->pfIsolationR03().sumChargedHadronPt;
  double neutralHadronIso = mu->pfIsolationR03().sumNeutralHadronEt;
  double photonIso = mu->pfIsolationR03().sumPhotonEt;
  
  double beta = mu->pfIsolationR03().sumPUPt;
  double pfRelIsoMu  = ( chargedHadronIso + TMath::Max ( 0.0 ,neutralHadronIso + photonIso - 0.5 * beta ) )/mu->pt() ;
  
  if(pfRelIsoMu >0.4) return false;
  return true;
}









bool TriggerAnalyzerRAWMiniAOD::PassOfflineElectronSelection(const pat::Electron * ele, reco::Vertex::Point PV){
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
  //In the next few lines one loops over all the trigger objects (corresponding to a given filter) and check whether one of them matches the reco object under study                                       
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
  //In the next few lines one loops over all the trigger objects (corresponding to a given filter) and check whether one of them matches the reco object under study                                       
  edm::Handle<edm::TriggerResults> trigResults;
  iEvent.getByToken(trgresultsHLT2Token_, trigResults);
  
  
  //Accessing the trigger objects in RAW/AOD
  //Printing here all trigger objects corresponding to the filter hltL3MuFiltered3
  edm::Handle<trigger::TriggerEvent> triggerObjectsSummary;
  iEvent.getByToken(trigobjectsRAWHLT2Token_ ,triggerObjectsSummary);
  trigger::TriggerObjectCollection selectedObjects;
  //  cout <<"triggerObjectsSummary.isValid(): " << triggerObjectsSummary.isValid()<< endl;
  if (triggerObjectsSummary.isValid()) {
    //    cout <<"triggerObjectsSummary.isValid()" <<endl;
    size_t filterIndex = (*triggerObjectsSummary).filterIndex( edm::InputTag(filtername,"","customhltnano") );
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
					      edm::EDGetTokenT<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > varToken_,  edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> candToken_,   bool  dividebyE, bool dividebyEt, double dRmatching , bool iset){

  double thevar = -1.;

  //Inspired from http://cmslxr.fnal.gov/source/HLTrigger/Egamma/src/HLTGenericFilter.cc        
  edm::Handle<trigger::TriggerFilterObjectWithRefs> PrevFilterOutput;
  iEvent.getByToken (candToken_, PrevFilterOutput);

  edm::Handle<edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > > > depMap;
  iEvent.getByToken (varToken_,depMap);

  std::vector<edm::Ref<std::vector<reco::RecoEcalCandidate> > > recoCands;


  if(PrevFilterOutput.isValid()&&  (depMap.isValid() ||iset) ){

    PrevFilterOutput->getObjects(trigger::TriggerCluster, recoCands);
    if(recoCands.empty())PrevFilterOutput->getObjects(trigger::TriggerPhoton, recoCands);

    double dRmin = dRmatching;
    for (unsigned int i=0; i<recoCands.size(); i++) {
      edm::Ref<std::vector<reco::RecoEcalCandidate> > ref = recoCands[i];
      float EtaSC = ref->eta();
      float PhiSC = ref->phi();

      if(deltaR(recoeta,recophi,EtaSC,PhiSC ) > dRmin )continue;
      dRmin = deltaR(recoeta,recophi,EtaSC,PhiSC ) ;
      float energy = ref->superCluster()->energy();
      float et = ref->superCluster()->energy() * sin (2*atan(exp(-ref->eta())));
      
      if(not iset) {
      typename edm::AssociationMap<edm::OneToValue<std::vector<reco::RecoEcalCandidate>, float > >::const_iterator mapi = (*depMap).find( ref );
      float vali = mapi->val;

      thevar = (double) vali;
      if(dividebyE)thevar = (double)vali/energy;
      if(dividebyEt)thevar =(double) vali/et;
      }
      else thevar = et;
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



//What follows is a copy of https://github.com/cms-sw/cmssw/blob/master/HLTrigger/Egamma/plugins/HLTElectronPixelMatchFilter.cc


float TriggerAnalyzerRAWMiniAOD::calDPhi1Sq(reco::ElectronSeedCollection::const_iterator seed, int charge) const {
  float sPhi1B_(0.0069), sPhi1I_(0.0088), sPhi1F_(0.0076);
  const float dPhi1Const = seed->subDet(0) == 1 ? seed->subDet(1) == 1 ? sPhi1B_ : sPhi1I_ : sPhi1F_;
  float dPhi1 = charge < 0 ? seed->dPhiNeg(0) / dPhi1Const : seed->dPhiPos(0) / dPhi1Const;
  return dPhi1 * dPhi1;
}

float TriggerAnalyzerRAWMiniAOD::calDPhi2Sq(reco::ElectronSeedCollection::const_iterator seed, int charge) const {
  float sPhi2B_(3.7e-4), sPhi2I_(7.0e-4), sPhi2F_(0.00906);
  const float dPhi2Const = seed->subDet(0) == 1 ? seed->subDet(1) == 1 ? sPhi2B_ : sPhi2I_ : sPhi2F_;
  float dPhi2 = charge < 0 ? seed->dPhiNeg(1) / dPhi2Const : seed->dPhiPos(1) / dPhi2Const;
  return dPhi2 * dPhi2;
}

float TriggerAnalyzerRAWMiniAOD::calDZ2Sq(reco::ElectronSeedCollection::const_iterator seed, int charge) const {
  float sZ2B_(0.012), sR2I_(0.027), sR2F_(0.04);
  const float dRZ2Const = seed->subDet(0) == 1 ? seed->subDet(1) == 1 ? sZ2B_ : sR2I_ : sR2F_;
  float dRZ2 = charge < 0 ? seed->dRZNeg(1) / dRZ2Const : seed->dRZPos(1) / dRZ2Const;
  return dRZ2 * dRZ2;
}


double TriggerAnalyzerRAWMiniAOD::PixelMatchVariable( const edm::Event& iEvent, double recoeta, double recophi, edm::EDGetTokenT<trigger::TriggerFilterObjectWithRefs> candToken_,   double dRmatching ){
  
  
  /*int HLTElectronPixelMatchFilter::getNrOfMatches(edm::Handle<reco::ElectronSeedCollection>& eleSeeds,
    reco::SuperClusterRef& candSCRef) const {*/
  
  /*float s2BarrelThres_(std::pow(std::atanh(0.35 ) * 10., 2)); 
  float s2InterThres_(std::pow(std::atanh(1.0 ) * 10., 2));
  float s2ForwardThres_(std::pow(std::atanh(1.0 ) * 10., 2));*/ 
  bool useS_ = false;
  
  double thevar = 0.;
  
  
  edm::Handle<trigger::TriggerFilterObjectWithRefs> PrevFilterOutput;
  iEvent.getByToken (candToken_, PrevFilterOutput);
  
  std::vector<edm::Ref<reco::RecoEcalCandidateCollection> > recoCands;
  
  edm::Handle<reco::ElectronSeedCollection> l1PixelSeeds;
  iEvent.getByToken(l1PixelSeedsToken_, l1PixelSeeds);
  
  if(PrevFilterOutput.isValid() ){
    PrevFilterOutput->getObjects(trigger::TriggerCluster, recoCands);
    
    if(recoCands.empty())PrevFilterOutput->getObjects(trigger::TriggerPhoton, recoCands);
    
    double dRmin = dRmatching;
    for (unsigned int i=0; i<recoCands.size(); i++) {
      edm::Ref<std::vector<reco::RecoEcalCandidate> > ref = recoCands[i];
      double provvar = 0;
      
      float EtaSC = ref->eta();
      float PhiSC = ref->phi();
      
      if(deltaR(recoeta,recophi,EtaSC,PhiSC ) > dRmin )continue;
      dRmin = deltaR(recoeta,recophi,EtaSC,PhiSC ) ;
      reco::SuperClusterRef recr2 = ref->superCluster();
      
      //Loop over pixel seeds
      for (auto seedIt = l1PixelSeeds->begin(); seedIt != l1PixelSeeds->end(); seedIt++) {
	edm::RefToBase<reco::CaloCluster> caloCluster = seedIt->caloCluster();
	reco::SuperClusterRef scRef = caloCluster.castTo<reco::SuperClusterRef>();
	if (&(*recr2) == &(*scRef)) {
	  
	  if (useS_) {
	    float s2Neg = calDPhi1Sq(seedIt, -1) + calDPhi2Sq(seedIt, -1) + calDZ2Sq(seedIt, -1);
	    float s2Pos = calDPhi1Sq(seedIt, 1) + calDPhi2Sq(seedIt, 1) + calDZ2Sq(seedIt, 1);
	    

	    if(thevar == 0 || thevar > s2Neg ||thevar > s2Pos)
	      thevar = abs(s2Neg)< abs(s2Pos) ? s2Neg : s2Pos;
	  }
	  else 
	    provvar+=1;
	}  //end sc ref match
	  
	}  //end loop over ele seeds
      if(provvar> thevar) thevar = provvar;

    }
  }

  return thevar;

}



//define this as a plug-in
DEFINE_FWK_MODULE(TriggerAnalyzerRAWMiniAOD);
