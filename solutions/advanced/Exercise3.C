#include "TMath.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TH1.h"
#include "TFile.h"
#include "TTree.h"

void Exercise3(){
	TFile* dataFile = new TFile("../../data/data_advanced_ex3.root","READ");
    TTree* data = ((TTree*)dataFile->Get("dataTree"))->CloneTree();
    data->SetDirectory(0);
    dataFile->Close();

    data->Print();
    Double_t m1,m2,m3,m4,m5;
    data->SetBranchAddress("m1",&m1);
    data->SetBranchAddress("m2",&m2);
    data->SetBranchAddress("m3",&m3);
    data->SetBranchAddress("m4",&m4);
    data->SetBranchAddress("m5",&m5);

    TH1F* hist1 = new TH1F("hist1",";m1",200,-20,20);
    TH1F* hist2 = new TH1F("hist2",";m2",200,-20,20);
    TH1F* hist3 = new TH1F("hist3",";m3",200,-20,20);
    TH1F* hist4 = new TH1F("hist4",";m4",200,-20,20);
    TH1F* hist5 = new TH1F("hist5",";m5",200,-20,20);

    Int_t nentries = data->GetEntries();
    for(int i=1;i<nentries;i++){
        data->GetEntry(i);
        hist1->Fill(m1);
        hist2->Fill(m2);
        hist3->Fill(m3);
        hist4->Fill(m4);
        hist5->Fill(m5);

    }

    TCanvas* c1 = new TCanvas("c1","m1");
    hist1->Draw();
    TCanvas* c2 = new TCanvas("c2","m2");
    hist2->Draw();
    TCanvas* c3 = new TCanvas("c3","m3");
    hist3->Draw();
    TCanvas* c4 = new TCanvas("c4","m4");
    hist4->Draw();
    TCanvas* c5 = new TCanvas("c5","m5");
    hist5->Draw();

    c1->SaveAs("Exercise3_c1.png");
    c2->SaveAs("Exercise3_c2.png");
    c3->SaveAs("Exercise3_c3.png");
    c4->SaveAs("Exercise3_c4.png");
    c5->SaveAs("Exercise3_c5.png");

}