/** @file PpZgParameters.hh
    @author Kolja Kauder
    @brief Common parameters
    @details Used to quickly include the same parameters into different macros.
    @date Mar 23, 2017
   
 */

#ifndef PPZGPARAMETERS_HH
#define PPZGPARAMETERS_HH

#include "JetAnalyzer.hh"

using fastjet::JetAlgorithm;
using fastjet::antikt_algorithm;
using fastjet::kt_algorithm;
using fastjet::cambridge_algorithm;

enum INTYPE{ MCTREE, INTREE, INPICO, MCPICO, HERWIGTREE };

// Subtract background?
enum BGTYPE{ NONE=0, AREA=1, CONSTSUBPRE=2, CONSTSUBPOST=3 };

// Return values for the main routine
enum class EVENTRESULT{
  PROBLEM,
  ENDOFINPUT,
  NOTACCEPTED,
  NOCONSTS,
  NOJETS,
  JETSFOUND
};

class PpZgParameters{

public :
  double R = 0.4;            ///< Resolution parameter ("radius").
  double z_cut = 0.10;       ///< Grooming cut parameter
  double beta  = 0.0;        ///< Grooming angular parameter

  /// Jet algorithm for the original jets
  JetAlgorithm LargeJetAlgorithm=fastjet::antikt_algorithm;
  // JetAlgorithm LargeJetAlgorithm = fastjet::cambridge_algorithm;
  
  /// Alternative reclustering to Cambridge/Aachen (at our own risk)
  bool CustomRecluster=false;
  JetAlgorithm CustomReclusterJetAlgorithm;
  // bool CustomRecluster=true;
  // JetAlgorithm CustomReclusterJetAlgorithm = fastjet::antikt_algorithm;
  bool Recursive=false;  ///< Repeat on subjets?

  /// Repetitions in the background. Anything other than 1 WILL NOT WORK because
  /// a) we're using explicit ghosts (though we don't have to)
  /// b) more importantly, the background subtractor contains fastjet::SelectorNHardest(2)
  ///    which doesn't work jet-by-jet and throws an error
  int GhostRepeat = 1;
  float GhostArea = 0.005;    ///< ghost area

  // int ghost_repeat = 1;
  // double ghost_area = 0.01;    ///< ghost area
  // const double ghost_area = 0.0005;    ///< ghost area

  // const double PtJetMin = 20.0;    ///< Min jet pT
  double PtJetMin = 7.0;      ///< Min jet pT
  double PtJetMax = 1000.0;   ///< Max jet pT
  double LeadPtMin=5.0;                 ///< leading jet minimum p<SUB>T</SUB>
    
  double MaxJetNEF=0.9;       ///< Max neutral energy fraction

  double EtaConsCut = 1.0;    ///< Constituent |&eta;| acceptance
  double PtConsMin=0.2;       ///< Constituent pT minimum
  // const double PtConsMin=2.0;       ///< Constituent pT minimum
  double PtConsMax=1000;        ///< Constituent pT maximum
  
  double RefMultCut=0;        ///< Reference multiplicity. Needs to be rethought to accomodate pp and AuAu
  
  double VzCut=30;            ///< Vertex z 
  // const double VzDiffCut=6;         ///< |Vz(TPC) - Vz(VPD)| <-- NOT WORKING in older data (no VPD)
  double VzDiffCut=1000;      ///< |Vz(TPC) - Vz(VPD)|
  
  double DcaCut=1.0;          ///< track dca
  double NMinFit=20;             ///< minimum number of fit points for tracks
  double FitOverMaxPointsCut=0.52; ///< NFit / NFitPossible

  double HadronicCorr = 0.9999; ///< Fraction of hadronic correction

  double FakeEff = 1.0; ///< fake efficiency for systematics. 0.95 is a reasonable example.

  Int_t IntTowScale=0;
  /// Tower GAIN: 4.8%
  Float_t fTowUnc=0.048;
  /// Tower scale for uncertainty;
  float fTowScale=1.0;
  

  
  // ************************************
  // Do NOT cut high tracks and towers!
  // Instead, reject the whole event when
  // of these is found
  // ************************************
  double MaxEtCut=1000;       ///< tower ET cut
  double MaxTrackPt=1000;     ///< track pT cut

  
  // EVENT rejection cuts
  double MaxEventPtCut=30;       ///< max track pT cut for event
  // double MaxEventEtCut=1000;       ///< max tower ET cut for event
  double MaxEventEtCut=30;       ///< max tower ET cut for event
  double MinEventEtCut=0;        ///< min event ET cut for event
  double ManualHtCut=0.0;        ///< necessary for some embedding picos. Should always equal MinEventEtCut


  BGTYPE SubtractBg=NONE;
  BGTYPE EmbSubtractBg=NONE;

  // BGTYPE SubtractBg=NONE;
  // BGTYPE EmbSubtractBg=NONE;

  // Geant files have messed up runid and event id.
  // Switch for fixing. Should be turned on by default for Geant files, off otherwise.
  bool UseGeantNumbering=false;

  // // MC example
  // // ----------
  // TString InputName = "Data/AlternateRhicPythia/LargeEtaPythiaOnly_1_ptHat=25_35.root"; ///< Input name
  // INTYPE intype = MCTREE;             ///< Input type (can be a pico dst, a result tree, an MC tree)
  // TString ChainName = "tree";         ///< Name of the input chain
  // TString TriggerName = "All";        ///< Trigger type (All, MB, HT, pp, ppHT, ppJP)
  
  // // MC example
  // // ----------
  // TString InputName = "Data/RhicPythia/RhicPythiaOnly_10_ptHat=20_23.root"; ///< Input name
  // INTYPE intype = MCTREE;             ///< Input type (can be a pico dst, a result tree, an MC tree)
  // TString ChainName = "tree";         ///< Name of the input chain
  // TString TriggerName = "All";        ///< Trigger type (All, MB, HT, pp, ppHT, ppJP)
  
  // // GEANTMC example
  // // ---------------
  // TString InputName = "Data/AddedGeantPythia/picoDst_25_35_0.root"; ///< Input name
  // INTYPE intype = MCPICO;             ///< Input type (can be a pico dst, a result tree, an MC tree)
  // TString ChainName = "JetTreeMc";    ///< Name of the input chain
  // TString TriggerName = "All";        ///< Trigger type (All, MB, HT, pp, ppHT, ppJP)
  
  // // GEANT example
  // // ---------------
  // TString InputName = "Data/AddedGeantPythia/picoDst_25_35_0.root"; ///< Input name
  // INTYPE intype = INPICO;             ///< Input type (can be a pico dst, a result tree, an MC tree)
  // TString ChainName = "JetTree";      ///< Name of the input chain
  // TString TriggerName = "All";        ///< Trigger type (All, MB, HT, pp, ppHT, ppJP)

  // GEANT12 example
  // ---------------
  TString InputName = "Data/AddedEmbedPythiaRun12pp200/Cleanpp12Pico_pt25_35_g0.root"; ///< Input name
  INTYPE intype = INPICO;             ///< Input type (can be a pico dst, a result tree, an MC tree)
  TString ChainName = "JetTree";      ///< Name of the input chain
  TString TriggerName = "ppJP2";        ///< Trigger type (All, MB, HT, pp, ppHT, ppJP2, ppJP(careful!))

  // // real data pico example
  // // ----------------------
  // TString InputName = "Data/ppHT/picoDst_7156028_32294A2A403C1B82D143E9E183B8E3B3*root"; ///< Input name
  // INTYPE intype = INPICO;                 ///< Input type (can be a pico dst, a result tree, an MC tree)
  // TString ChainName = "JetTree";          ///< Name of the input chain
  // TString TriggerName = "ppHT";           ///< Trigger type (All, MB, HT, pp, ppHT, ppJP)
    
  // // real data pico example run 12
  // // -----------------------------
  // TString InputName = "Data/ppJP2Run12/sum8.root"; ///< Input name
  // INTYPE intype = INPICO;                 ///< Input type (can be a pico dst, a result tree, an MC tree)
  // TString ChainName = "JetTree";          ///< Name of the input chain
  // TString TriggerName = "ppJP2";           ///< Trigger type (All, MB, HT, pp, ppHT, ppJP)

  // // real AuAu data pico example
  // // -------------------
  // TString InputName = "Data/SmallAuAu/Small_Clean809.root"; ///< Input name
  // INTYPE intype = INPICO;                 ///< Input type (can be a pico dst, a result tree, an MC tree)
  // TString ChainName = "JetTree";          ///< Name of the input chain
  // TString TriggerName = "HT";           ///< Trigger type (All, MB, HT, pp, ppHT, ppJP)

  // Allow Embedding
  // ---------------
  // NONE
  TString EmbInputName = "";           ///< Embedding input name. Leave blank for no embedding
  INTYPE Embintype = MCTREE;           ///< Embedding input type (can be a pico dst, a result tree, an MC tree)
  TString EmbChainName = "";           ///< Name of the embedding input chain
  TString EmbTriggerName = "none";       ///< Embedding trigger type (All, MB, HT, pp, ppHT, ppJP)

  // // This is equivalent to -embi FAKERHIC
  // TString EmbInputName = "Data/FakeAuAu20_*root";           ///< Embedding input name. Leave blank for no embedding
  // INTYPE Embintype = MCTREE;           ///< Embedding input type (can be a pico dst, a result tree, an MC tree)
  // TString EmbChainName = "tree";       ///< Name of the embedding input chain
  // TString EmbTriggerName = "All";       ///< Embedding trigger type (All, MB, HT, pp, ppHT, ppJP)

  // // real data  
  // TString EmbInputName = "";           ///< Embedding input name. Leave blank for no embedding
  // INTYPE Embintype = MCTREE;           ///< Embedding input type (can be a pico dst, a result tree, an MC tree)
  // TString EmbChainName = "tree";       ///< Name of the embedding input chain
  // TString EmbTriggerName = "MB";       ///< Embedding trigger type (All, MB, HT, pp, ppHT, ppJP)

  
  int nMix=1;                   ///< How many events to mix

  // Only putting it here so that it can be initialized in the analysis class and then used
  TString OutFileName = "TmpResult.root";     ///< Output file


};
#endif // PPZGPARAMETERS_HH
