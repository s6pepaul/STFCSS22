//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Mar 24 13:27:13 2022 by ROOT version 6.24/06
// from TTree dataTree/dataTree
// found on file: ../../data/data_advanced_ex3.root
//////////////////////////////////////////////////////////

#ifndef Exercise4_h
#define Exercise4_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

#include "TH1.h"
#include "TF1.h"

// Headers needed by this particular selector


class Exercise4 : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<Double_t> m1 = {fReader, "m1"};
   TTreeReaderValue<Double_t> m2 = {fReader, "m2"};
   TTreeReaderValue<Double_t> m3 = {fReader, "m3"};
   TTreeReaderValue<Double_t> m4 = {fReader, "m4"};
   TTreeReaderValue<Double_t> m5 = {fReader, "m5"};


   Exercise4(TTree * /*tree*/ =0) { }
   virtual ~Exercise4() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   TH1F* hist_m1;
   TH1F* hist_m2;
   TH1F* hist_m3;
   TH1F* hist_m4;
   TH1F* hist_m5;


   ClassDef(Exercise4,0);

};

#endif

#ifdef Exercise4_cxx
void Exercise4::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t Exercise4::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef Exercise4_cxx
