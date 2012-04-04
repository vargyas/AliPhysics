#ifndef ALIANALYSISTASKCHARGEDHADRONSPECTRA_H
#define ALIANALYSISTASKCHARGEDHADRONSPECTRA_H

//////////////////////////////////////////////////////////////////////////////
//                                                                          //
// This analysis extracts pT-spectra of charged kaons, protons, and pions.  //
// It is based on particles identifation via the dE/dx signal of the TPC.   //
//                                                                          //
//////////////////////////////////////////////////////////////////////////////

class TH1;
class TH1F;
class TH2D;
class TH3D;
class TList;
class TObjArray;
class AliESDEvent;
class AliESDtrack;
class AliESDtrackCuts;
class AliHeader;
class AliESDpid;


#include "AliAnalysisTaskSE.h"
#include "THnSparse.h"

class AliAnalysisCombinedHadronSpectra : public AliAnalysisTaskSE {
 public:
  AliAnalysisCombinedHadronSpectra(const char *name);
  AliAnalysisCombinedHadronSpectra();
  virtual ~AliAnalysisCombinedHadronSpectra() {}
  //
  virtual void   UserCreateOutputObjects();
  virtual void   UserExec(Option_t *option);
  virtual void   Terminate(Option_t *);
  //
  Bool_t         SelectOnImpPar(AliESDtrack* t);
  //
  void           SetESDtrackCuts(AliESDtrackCuts * trackCuts){fESDtrackCuts = trackCuts;};
  void           SetAlephParameters(const Double_t * parameters){for(Int_t j=0;j<5;j++) fAlephParameters[j] = parameters[j]; Initialize();};
  void           SetIsMCtrue(Bool_t isMCdata = kTRUE){fMCtrue = isMCdata;};
  void           SetUseHBTmultiplicity(Bool_t useHBTmultiplicity = kTRUE){fUseHBTmultiplicity = useHBTmultiplicity;};
  void		 SetUseTPConlyTracks(Bool_t useTPConlyTracks = kTRUE){fUseTPConlyTracks = useTPConlyTracks;};
  void           SetSaveMotherPDG(Bool_t saveMotherPDG =kTRUE){fSaveMotherPDG = saveMotherPDG;};
  void           Initialize();
  //
  
 private:
  //
  void  BinLogAxis(const TH1 *h);
  Int_t GetPythiaEventProcessType(const AliHeader* aHeader, const Bool_t adebug = kFALSE) const;
  //
  AliESDEvent *fESD;                   //! ESD object
  TList       *fListHist;              //! list for histograms
  //
  AliESDtrackCuts * fESDtrackCuts;     // basic cut variables
  AliESDtrackCuts * fESDTrackCutsMult; // cuts for the MULTIPLICITY DETERMINATION
  AliESDpid       * fESDpid;           // basic TPC object for n-sigma cuts
  Bool_t        fMCtrue;               // flag if real data or MC is processed
  Bool_t        fOnlyQA;               // flag if only QA histograms should be filled
  Bool_t        fUseHBTmultiplicity;   // flag if multiplicity determination should be done as in the HBT paper
  Bool_t	fUseTPConlyTracks;     // flag if TPConly-track should be used
  Bool_t        fSaveMotherPDG;        // flag if PDG of mother should be saved (weak decays)
  Double_t      fAlephParameters[5];   // Aleph Parameters for Bethe-Bloch
  //
  //
  //
  THnSparseF * fHistRealTracks;        //! histogram with all necessary information for real tracks
  THnSparseF * fHistMCparticles;       //! histogram with all necessary information for MC particles
  //
  TH3D       * fHistPidQA;             //! histogram for the QA of the PID
  TH2D       * fHistMult;              //! control histogram for multiplicity
  TH1D       * fHistCentrality;        //! control histogram for centrality
  //
  AliAnalysisCombinedHadronSpectra(const AliAnalysisCombinedHadronSpectra&); 
  AliAnalysisCombinedHadronSpectra& operator=(const AliAnalysisCombinedHadronSpectra&); 

  ClassDef(AliAnalysisCombinedHadronSpectra, 1); 
};

#endif
