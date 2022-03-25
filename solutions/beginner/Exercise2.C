#include "TMath.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TFile.h"
#include "TGraph.h"
#include "TGraphErrors.h"


void Exercise2(){
    
    /*******************/
	/***** PART 1 ******/
    Double_t x[10] = {0,1,2,3,4,5,6,7,8,9};
    Double_t y[10] = {0,2.1,1.2,4.3,3.4,5.5,4.6,7.7,9.8,8.9};
    TGraph* g = new TGraph(10,x,y);
    g->SetNameTitle("graph","graph");

    TCanvas* c1 = new TCanvas("c1","TGraph");
    g->Draw();

    /******* Save results ********/
	c1->SaveAs("Exercise2a.png");

    /*******************/
	/***** PART 2 ******/
    Double_t dx[10] = {0.1,.1,.2,.3,.4,.5,.6,.7,.8,.9};
    Double_t dy[10] = {0.1,.1,.2,.3,.4,.5,.6,.7,.8,.9};
    TCanvas* c2 = new TCanvas("c2","TGraphErrors");
    TGraphErrors* ge = new TGraphErrors(10,x,y,dx,dy);
    ge->SetNameTitle("errorgraph","errorgraph");
    ge->Draw();

    /******* Save results ********/
	c2->SaveAs("Exercise2b.png");

	/*****************************/
	TFile* outfile = new TFile("ex2.root", "RECREATE");
	g->Write();
	ge->Write();
	outfile->Close();
}