#include "TMath.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TH1.h"
#include "TFile.h"

void Exercise2(){
	TFile* data = new TFile("../../data/data_advanced_ex2.root","READ");
    TH1F* hist1 = (TH1F*)(data->Get("h1"))->Clone("hist1");
    hist1->SetDirectory(0);
    TH1F* hist2 = (TH1F*)(data->Get("h2"))->Clone("hist2");
    hist2->SetDirectory(0);
    TH1F* hist3 = (TH1F*)(data->Get("h3"))->Clone("hist3");
    hist3->SetDirectory(0);
    TH1F* hist4 = (TH1F*)(data->Get("h4"))->Clone("hist4");
    hist4->SetDirectory(0);
    TH1F* hist5 = (TH1F*)(data->Get("h5"))->Clone("hist5");
    hist5->SetDirectory(0);
    data->Close();

    
    TCanvas* c1 = new TCanvas("c1");
    hist1->Draw();
	TF1* f1 = new TF1("f1","[0]*TMath::Gaus(x,[1],[2])",-20,20);
    f1->SetParameters(100,5,2);
    f1->SetParLimits(2,0,1000);
    hist1->Fit(f1);
    Double_t yield1 = TMath::Sqrt(2*TMath::Pi())*f1->GetParameter("p0")*f1->GetParameter("p2")*hist1->GetNbinsX()/(hist1->GetBinLowEdge(hist1->GetNbinsX()+1)-hist1->GetBinLowEdge(1));
    std::cout << "Yield in hist1: " << yield1 << std::endl;


    TCanvas* c2 = new TCanvas("c2");
    hist2->Draw();
	TF1* f2 = new TF1("f2","[0]*TMath::Gaus(x,[1],[2])+[3]+[4]*x",-20,20);
    f2->SetParameters(100,0,2,20,1);
    f2->SetParLimits(2,0,1000);
    hist2->Fit(f2);
    Double_t yield2 = TMath::Sqrt(2*TMath::Pi())*f2->GetParameter("p0")*f2->GetParameter("p2")*hist2->GetNbinsX()/(hist2->GetBinLowEdge(hist2->GetNbinsX()+1)-hist2->GetBinLowEdge(1));
    std::cout << "Yield in hist2: " << yield2 << std::endl;


    TCanvas* c3 = new TCanvas("c3");    
    hist3->Draw();
	TF1* f3 = new TF1("f3","[0]*TMath::Gaus(x,[1],[2])+[3]+[4]*x",-20,20);
    f3->SetParameters(100,0,2,20,1);
    f3->SetParLimits(2,0,1000);
    hist3->Fit(f3);
    Double_t yield3 = TMath::Sqrt(2*TMath::Pi())*f3->GetParameter("p0")*f3->GetParameter("p2")*hist3->GetNbinsX()/(hist3->GetBinLowEdge(hist3->GetNbinsX()+1)-hist3->GetBinLowEdge(1));
    std::cout << "Yield in hist3: " << yield3 << std::endl;


    TCanvas* c4 = new TCanvas("c4");    
    hist4->Draw();
	TF1* f4 = new TF1("f4","[0]*TMath::Gaus(x,[1],[2])+[3]+[4]*x",-20,20);
    f4->SetParameters(100,0,2,20,1);
    f4->SetParLimits(2,0,1000);
    hist4->Fit(f4);
    Double_t yield4 = TMath::Sqrt(2*TMath::Pi())*f4->GetParameter("p0")*f4->GetParameter("p2")*hist4->GetNbinsX()/(hist4->GetBinLowEdge(hist4->GetNbinsX()+1)-hist4->GetBinLowEdge(1));
    std::cout << "Yield in hist4: " << yield4 << std::endl;


    TCanvas* c5 = new TCanvas("c5");    
    hist5->Draw();
	TF1* f5 = new TF1("f5","[0]*TMath::Gaus(x,[1],[2])+[3]+[4]*x+[5]*x*x",-20,20);
    f5->SetParameters(100,0,2,20,1,1);
    f5->SetParLimits(2,0,1000);
    hist5->Fit(f5);
    Double_t yield5 = TMath::Sqrt(2*TMath::Pi())*f5->GetParameter("p0")*f5->GetParameter("p2")*hist5->GetNbinsX()/(hist5->GetBinLowEdge(hist5->GetNbinsX()+1)-hist5->GetBinLowEdge(1));
    std::cout << "Yield in hist5: " << yield5 << std::endl;

    c1->SaveAs("Exercise2_c1.png");
    c2->SaveAs("Exercise2_c2.png");
    c3->SaveAs("Exercise2_c3.png");
    c4->SaveAs("Exercise2_c4.png");
    c5->SaveAs("Exercise2_c5.png");

}