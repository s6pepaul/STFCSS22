#include <TROOT.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "TGenPhaseSpace.h"
#include "TFile.h"
#include "TRandom3.h"
#include "TH1F.h"
#include "TTree.h"

Bool_t mockAcceptance(TLorentzVector vec);
TLorentzVector smearNeutral(TLorentzVector vec);
TLorentzVector smearCharged(TLorentzVector vec);

void Exercise1(){

    Int_t NEVENTS = 10000;
    Double_t TARGET_MASS = 0.938272081;

    Int_t NUM_PARTICLES = 3;
    Double_t TSLOPE = 3.0;

    Double_t P1_MASS = 0.;
    Double_t P2_MASS = 0.;
    Double_t P3_MASS = 0.938272081;
    Double_t ISOBAR_MASS = 0.1349768;

	Double_t IsobarMasses[2] = {ISOBAR_MASS,P3_MASS};
	Double_t IsobarDecayMasses[2] = {P1_MASS,P2_MASS};
	
	Double_t weight=1.0;
	Double_t maxWeight;
	static TRandom3 *randnum = new TRandom3(1);

  
    Double_t photonEnergy = 9;    // beam particle
    TLorentzVector lGenBeam(0.0,0.0,photonEnergy,photonEnergy);  // photon beam
    TLorentzVector lGenTarget(0.0, 0.0, 0.0, TARGET_MASS); //proton target
    TLorentzVector lGenW = lGenBeam + lGenTarget;                        //add beam and target  
    TLorentzVector *lGenP1,*lGenP2,*lGenP3,*lGenpion; //various final state particles
    TLorentzVector **lAllGen[]={&lGenP1,&lGenP2,&lGenP3}; //array of all
    Double_t uniqueID=0;

    TGenPhaseSpace* IsobarEvent=new TGenPhaseSpace();
    TGenPhaseSpace* IsobarDecayEvent=new TGenPhaseSpace();

    TH1F* hist_gen_protonMass = new TH1F("hist_gen_protonMass",";mass",200,0,1);
    TH1F* hist_gen_pionMass = new TH1F("hist_gen_pionMass",";mass",200,0,1);
    TH1F* hist_gen_pionPhi = new TH1F("hist_gen_pionPhi",";#phi",200,-3.2,3.2);
    TH1F* hist_gen_pionCosTheta = new TH1F("hist_gen_pionCosTheta",";cos(#theta)",200,-1,1);
    TH1F* hist_gen_pionCosThetaCMS = new TH1F("hist_gen_pionCosThetaCMS",";cos(#theta_{CMS})",200,-1,1);
    TH1F* hist_gen_protonTheta = new TH1F("hist_gen_protonTheta",";#theta_{p}",200,0,3.2);
    TH1F* hist_gen_gammaTheta = new TH1F("hist_gen_gammaTheta",";#theta_{#gamma}",200,0,3.2);
    TH1F* hist_gen_gammaE = new TH1F("hist_gen_gammaE",";E_{#gamma}",200,0,10);
    TH1F* hist_gen_protonP = new TH1F("hist_gen_protonP",";P_{p}",200,0,10);
    TH1F* hist_gen_momT = new TH1F("hist_gen_momT",";mom t",100,0,2);

    TH1F* hist_reco_protonMass = new TH1F("hist_reco_protonMass",";mass",200,0,1);
    TH1F* hist_reco_pionMass = new TH1F("hist_reco_pionMass",";mass",200,0,1);
    TH1F* hist_reco_pionPhi = new TH1F("hist_reco_pionPhi",";#phi",200,-3.2,3.2);
    TH1F* hist_reco_pionCosTheta = new TH1F("hist_reco_pionCosTheta",";cos(#theta)",200,-1,1);
    TH1F* hist_reco_pionCosThetaCMS = new TH1F("hist_reco_pionCosThetaCMS",";cos(#theta_{CMS})",200,-1,1);
    TH1F* hist_reco_protonTheta = new TH1F("hist_reco_protonTheta",";#theta_{p}",200,0,3.2);
    TH1F* hist_reco_gammaTheta = new TH1F("hist_reco_gammaTheta",";#theta_{#gamma}",200,0,3.2);
    TH1F* hist_reco_gammaE = new TH1F("hist_reco_gammaE",";E_{#gamma}",200,0,10);
    TH1F* hist_reco_protonP = new TH1F("hist_reco_protonP",";P_{p}",200,0,10);
    TH1F* hist_reco_momT = new TH1F("hist_reco_momT",";mom t",100,0,2);

    TH1F* hist_diff_protonMass = new TH1F("hist_diff_protonMass",";mass",200,-1,1);
    TH1F* hist_diff_pionMass = new TH1F("hist_diff_pionMass",";mass",200,-1,1);
    TH1F* hist_diff_pionPhi = new TH1F("hist_diff_pionPhi",";#phi",200,-1,1);
    TH1F* hist_diff_pionCosTheta = new TH1F("hist_diff_pionCosTheta",";cos(#theta)",200,-1,1);
    TH1F* hist_diff_pionCosThetaCMS = new TH1F("hist_diff_pionCosThetaCMS",";cos(#theta_{CMS})",200,-1,1);
    TH1F* hist_diff_protonTheta = new TH1F("hist_diff_protonTheta",";#theta_{p}",200,-1,1);
    TH1F* hist_diff_gammaTheta = new TH1F("hist_diff_gammaTheta",";#theta_{#gamma}",200,-1,1);
    TH1F* hist_diff_gammaE = new TH1F("hist_diff_gammaE",";E_{#gamma}",200,-1,1);
    TH1F* hist_diff_protonP = new TH1F("hist_diff_protonP",";P_{p}",200,-1,1);
    TH1F* hist_diff_momT = new TH1F("hist_diff_momT",";mom t",200,-1,1);


    Int_t GeneratedEventsCounter=0;
    Int_t eventCounter=0;
    for(eventCounter;GeneratedEventsCounter<NEVENTS;eventCounter++){

        //make all final state parts NULL
        for(Int_t n=0;n<NUM_PARTICLES;n++){*lAllGen[n]=NULL;};

        // first "decay"
        if(!IsobarEvent->SetDecay(lGenW,2,IsobarMasses))
            continue;
        maxWeight = IsobarEvent->GetWtMax();
    		// cout << maxWeight << endl;
        while(kTRUE){
            Double_t currWeight = IsobarEvent->Generate();
            Double_t randWeight = randnum->Uniform(0,maxWeight);
            if( std::isnan(currWeight) || (randWeight <= currWeight) )
                break;
        }
        // get decay particles
        lGenpion=IsobarEvent->GetDecay(0);
        lGenP3=IsobarEvent->GetDecay(1);

        //now decay the isobar into final state
        if(!IsobarDecayEvent->SetDecay(*lGenpion,2,IsobarDecayMasses))
            continue;
        maxWeight = IsobarDecayEvent->GetWtMax();
        while(kTRUE){
            Double_t currWeight = IsobarDecayEvent->Generate();
            Double_t randWeight = randnum->Uniform(0,maxWeight);
            if( std::isnan(currWeight) || (randWeight <= currWeight) )
                break;
        }
        lGenP1=IsobarDecayEvent->GetDecay(0);
        lGenP2=IsobarDecayEvent->GetDecay(1);
        
        //add t-slope
        Double_t eventTSlope = 0;
        eventTSlope = (lGenBeam-*lGenpion).M2();
        Double_t rndTSlopeVal = randnum->Uniform(0,1);
        if(rndTSlopeVal > TMath::Exp(TSLOPE*eventTSlope)){
            continue;
        }

        //add phi distribution
        Double_t eventPhi = 0;
        eventPhi = (*lGenpion).Phi();
        Double_t rndPhi = randnum->Uniform(0,2);
        if(rndPhi > 1-0.2*TMath::Cos(2*(eventPhi-0.3))){
            continue;
        }

        //add mock detector
        if(!mockAcceptance(*lGenP1) || !mockAcceptance(*lGenP2) || !mockAcceptance(*lGenP3))
            continue;

        GeneratedEventsCounter++;

        /******************************/
        /**** diagnostic plots ********/
        /******************************/
        // generated
        TLorentzVector pion = (*lGenP1)+(*lGenP2);
        //boost into CMS frame to check theta distribution
		TLorentzVector locInitialStateP4 = lGenBeam + lGenTarget;
		TVector3 locBoostVector_ProdCMS = -1.0*(locInitialStateP4.BoostVector()); //negative due to coordinate system convention
        TLorentzVector pionCMS(pion);
		pionCMS.Boost(locBoostVector_ProdCMS);

        hist_gen_protonMass->Fill((*lGenP3).M());
        hist_gen_pionMass->Fill(pion.M());
        hist_gen_pionPhi->Fill(pion.Phi());
        hist_gen_pionCosTheta->Fill(pion.CosTheta());
        hist_gen_pionCosThetaCMS->Fill(pionCMS.CosTheta());
        hist_gen_momT->Fill(-1.*eventTSlope);
        hist_gen_gammaTheta->Fill((*lGenP1).Theta());
        hist_gen_gammaTheta->Fill((*lGenP2).Theta());
        hist_gen_protonTheta->Fill((*lGenP3).Theta());
        hist_gen_gammaE->Fill((*lGenP1).E());
        hist_gen_gammaE->Fill((*lGenP2).E());
        hist_gen_protonP->Fill((*lGenP3).P());

        //smeared ("reconstructed")
        TLorentzVector recGamma1 = smearNeutral(*lGenP1);
        TLorentzVector recGamma2 = smearNeutral(*lGenP2);
        TLorentzVector recProton = smearCharged(*lGenP3);
        TLorentzVector recPion = recGamma1+recGamma2;
        TLorentzVector recPionCMS(recPion); //assume initial state is known very well (i.e. don't smear)
		recPionCMS.Boost(locBoostVector_ProdCMS);
        Double_t receventTSlope = (lGenBeam-recPion).M2();

        hist_reco_protonMass->Fill(recProton.M());
        hist_reco_pionMass->Fill(recPion.M());
        hist_reco_pionPhi->Fill(recPion.Phi());
        hist_reco_pionCosTheta->Fill(recPion.CosTheta());
        hist_reco_pionCosThetaCMS->Fill(recPionCMS.CosTheta());
        hist_reco_momT->Fill(-1.*receventTSlope);
        hist_reco_gammaTheta->Fill(recGamma1.Theta());
        hist_reco_gammaTheta->Fill(recGamma2.Theta());
        hist_reco_protonTheta->Fill(recProton.Theta());
        hist_reco_gammaE->Fill(recGamma1.E());
        hist_reco_gammaE->Fill(recGamma2.E());
        hist_reco_protonP->Fill(recProton.P());

        //differences gen-smeared
        hist_diff_protonMass->Fill((*lGenP3).M()-recProton.M());
        hist_diff_pionMass->Fill(pion.M()-recPion.M());
        hist_diff_pionPhi->Fill(pion.Phi()-recPion.Phi());
        hist_diff_pionCosTheta->Fill(pion.CosTheta()-recPion.CosTheta());
        hist_diff_pionCosThetaCMS->Fill(pionCMS.CosTheta()-recPionCMS.CosTheta());
        hist_diff_momT->Fill(-1.*(eventTSlope-receventTSlope));
        hist_diff_gammaTheta->Fill((*lGenP1).Theta()-recGamma1.Theta());
        hist_diff_gammaTheta->Fill((*lGenP2).Theta()-recGamma2.Theta());
        hist_diff_protonTheta->Fill((*lGenP3).Theta()-recProton.Theta());
        hist_diff_gammaE->Fill((*lGenP1).E()-recGamma1.E());
        hist_diff_gammaE->Fill((*lGenP2).E()-recGamma2.E());
        hist_diff_protonP->Fill((*lGenP3).P()-recProton.P());

    }//event gen loop
    std::cout << "Generated " << eventCounter << " events. Kept " << GeneratedEventsCounter << " events." << std::endl;

    TFile* out = new TFile("results.root", "RECREATE");
    hist_gen_protonMass->Write();
    hist_gen_pionMass->Write();
    hist_gen_pionPhi->Write();
    hist_gen_pionCosTheta->Write();
    hist_gen_pionCosThetaCMS->Write();
    hist_gen_momT->Write();
    hist_gen_gammaTheta->Write();
    hist_gen_protonTheta->Write();
    hist_gen_gammaE->Write();
    hist_gen_protonP->Write();

    hist_reco_protonMass->Write();
    hist_reco_pionMass->Write();
    hist_reco_pionPhi->Write();
    hist_reco_pionCosTheta->Write();
    hist_reco_pionCosThetaCMS->Write();
    hist_reco_momT->Write();
    hist_reco_gammaTheta->Write();
    hist_reco_protonTheta->Write();
    hist_reco_gammaE->Write();
    hist_reco_protonP->Write();

    hist_diff_protonMass->Write();
    hist_diff_pionMass->Write();
    hist_diff_pionPhi->Write();
    hist_diff_pionCosTheta->Write();
    hist_diff_pionCosThetaCMS->Write();
    hist_diff_momT->Write();
    hist_diff_gammaTheta->Write();
    hist_diff_protonTheta->Write();
    hist_diff_gammaE->Write();
    hist_diff_protonP->Write();
    out->Close();
}

Bool_t mockAcceptance(TLorentzVector vec){
    if(vec.Theta()*TMath::RadToDeg()<5)
        return kFALSE;
    if(vec.Theta()*TMath::RadToDeg()>25 && vec.Theta()*TMath::RadToDeg()<30)
        return kFALSE;
    if(vec.Theta()*TMath::RadToDeg()>140)
        return kFALSE;

    return kTRUE;
}

TLorentzVector smearNeutral(TLorentzVector vec){
    static TRandom3 *rnd = new TRandom3(5);
    TLorentzVector smearedVec(vec);
    Double_t e = vec.E();
    Double_t smearedE = e+rnd->Gaus(0,0.10*e);
    Double_t scale = smearedE/e;
    smearedVec.SetE(smearedE);
    smearedVec.SetPx(vec.Px()*scale); // scale to make sure that M(gamma)=0
    smearedVec.SetPy(vec.Py()*scale);
    smearedVec.SetPz(vec.Pz()*scale);
    return smearedVec;
}

TLorentzVector smearCharged(TLorentzVector vec){
    static TRandom3 *rnd = new TRandom3(15);
    TLorentzVector smearedVec(vec);
    smearedVec.SetPx(vec.Px()+rnd->Gaus(0,0.02*vec.Px()));
    smearedVec.SetPy(vec.Py()+rnd->Gaus(0,0.02*vec.Py()));
    smearedVec.SetPz(vec.Pz()+rnd->Gaus(0,0.05*vec.Pz()));
    smearedVec.SetE(TMath::Sqrt(smearedVec.P()*smearedVec.P() + vec.M()*vec.M()));
    return smearedVec;
}