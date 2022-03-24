#include "TMath.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TH1.h"
#include "TFile.h"
#include "TTree.h"
#include "TLorentzVector.h"

void CreateData(){

    /******Ex 2.2********/
    TFile* outfile = new TFile("data_advanced_ex2.root", "RECREATE");
    TH1F* h1 = new TH1F("h1","",400,-20,20);
    TH1F* h2 = new TH1F("h2","",400,-20,20);
    TH1F* h3 = new TH1F("h3","",400,-20,20);
    TH1F* h4 = new TH1F("h4","",400,-20,20);
    TH1F* h5 = new TH1F("h5","",400,-20,20);
	TF1* f1 = new TF1("f1","gaus(0)",-20,20);
	TF1* f2 = new TF1("f2","pol2(0)",-20,20);
	f1->SetParameters(1,5,1);
	h1->FillRandom("f1",5000);
    h1->Write();

	f1->SetParameters(1,0,0.5);
	f2->SetParameters(100,2,0);
	h2->FillRandom("f1",7500);
	h2->FillRandom("f2",8000);
    h2->Write();

	f1->SetParameters(1,10,1);
	f2->SetParameters(100,3,0);
	h3->FillRandom("f1",3200);
	h3->FillRandom("f2",23000);
    h3->Write();

	f1->SetParameters(1,1,4);
	f2->SetParameters(100,1,0);
	h4->FillRandom("f1",11700);
	h4->FillRandom("f2",15000);
    h4->Write();

	f1->SetParameters(1,-3,2);
	f2->SetParameters(100,1.3,3);
	h5->FillRandom("f1",2800);
	h5->FillRandom("f2",5000);
    h5->Write();
    outfile->Close();

    /******Ex 2.3********/
    TFile* outfileTree = new TFile("data_advanced_ex3.root", "RECREATE");
    TTree* dataTree = new TTree("dataTree","dataTree");
    Double_t m1,m2,m3,m4,m5;
    dataTree->Branch("m1", &m1);
    dataTree->Branch("m2", &m2);
    dataTree->Branch("m3", &m3);
    dataTree->Branch("m4", &m4);
    dataTree->Branch("m5", &m5);
    
	TF1* fm1 = new TF1("fm1","gaus(0)",0,20);
    fm1->SetParameters(1,1.6,0.4);
    TF1* fm2 = new TF1("fm2","gaus(0)",0,20);
    fm2->SetParameters(1,5,3);
	TF1* fm3 = new TF1("fm3","1+[0]*TMath::Cos(2*(x+[1]))",-1,1);
    fm3->SetParameters(0.3,0.2);
	TF1* fm4 = new TF1("fm4","1+[0]*TMath::Sin(2*(x+[1]))",-TMath::Pi(),TMath::Pi());
    fm4->SetParameters(0.6,-0.1);
    TF1* fm5 = new TF1("fm5","1+[0]*TMath::Sin(2*(x+[1]))*TMath::Cos(2*(x+[2]))",-TMath::Pi(),TMath::Pi());
    fm5->SetParameters(0.6,-0.1,0.2);

    for(int i=0; i<20000; i++){
        m1 = fm1->GetRandom();
        m2 = fm2->GetRandom();
        m3 = TMath::ACos(fm3->GetRandom());
        m4 = fm4->GetRandom();
        m5 = fm5->GetRandom();
        dataTree->Fill();

    }
    dataTree->Write();
    outfileTree->Close();
}