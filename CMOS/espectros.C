/*16/05/2024
autores: E. Depaoli*/

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm> 
#include <TROOT.h>
#include "TFile.h"
#include "TTree.h"
#include "TObject.h"
#include "TString.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "TLatex.h"
#include "TStyle.h"
#include "TLine.h"
#include "TLegend.h"
#include "TSystem.h"
#include "TGaxis.h"
#include "TObjString.h"
#include "TH2D.h"
#include "TGraphErrors.h"
using std::cout; using std::vector; using std::string; using std :: copy;
//Function declaration//////////////////////////////////////////////////
void Enable_and_Set_Branches(TTree* & tree);
///////////////////////////////////////////////////////////////////////
//Variables a leer del tree hitSumm//
int flag;//error code
Float_t E0;//total energy of the "level 0" pixels
Float_t n0;//number of "level 0" pixels
Float_t E1;//including "level 1" pixels

//Rutas a las mediciones//
string filename{"/home/dario/Documentos/Lambda/CMOS/events.root"};

//Calibraciones//
double gan = 2.0;//[e-/ADU] ganancia medida por Lara y Mora
double electroenergy = 3.75;//[eV] energía necesaria para ionizar 1 e- del Si. Medido por Darío. 
double energia{0};
//Histograma de energia
int nbines = 500;//cantidad de intervalos
float emaxbin = 3125*8/1000;//[keV] límite superior histograma 6000
float eminbin = 0;//[keV] límite inferior histograma
TH1D * cm_1_bis_h = new TH1D("E1", "E1", nbines, eminbin, emaxbin);

///////////////////////////////////////////////////////////////////////
void espectros(){
	//Openning files, enabling branches
	TFile * f_1cmbis = TFile::Open(filename.c_str(),"READ");//abro el archivo //c_str() converts a string to an array of characters.
	if (!f_1cmbis->IsOpen()) {std::cerr << "Failed to load file" << filename << std::endl;}
	TTree * t_1cmbis = (TTree*) f_1cmbis->Get("hitSumm");//retrieves the tree from the file
	int Entries_1cmbis = t_1cmbis -> GetEntries();//
	Enable_and_Set_Branches(t_1cmbis);//Prendo las ramas que me interesan del tree que guarda los datos de distribucion de la carga en la imagen
	
	for(int k{0}; k < Entries_1cmbis;++k){
		t_1cmbis->GetEntry(k);// valores del evento k copiados a memoria
		if(flag == 0){
			energia = E1*gan*electroenergy/1000;
			cm_1_bis_h->Fill(energia);//E0*gan*electroenergy
		}

	}

	//Gráficos//////////////////////////////////////////////////////////////
	TCanvas * c1 = new TCanvas("Am 241", "Am 241", 2000, 1000);
    gStyle->SetOptTitle(1);
    gStyle->SetOptStat(0);
    c1->Divide(1,2);
    c1->SetLogy();
    c1->SetGrid();
    cm_1_bis_h -> SetTitle("Am-241");//Fuente electrodepositada
    cm_1_bis_h->Draw("E0");
    cm_1_bis_h->SetLineWidth(2);
    cm_1_bis_h->SetMarkerStyle(22);
    cm_1_bis_h->SetLineColor(kRed+1);
    cm_1_bis_h->SetMarkerColor(kRed+1);
    cm_1_bis_h->GetXaxis()->SetTitle("Energia [keV]");
    cm_1_bis_h->GetYaxis()->SetTitle("Frecuencia");
    cm_1_bis_h->GetXaxis()->SetTitleSize(0.05);
    cm_1_bis_h->GetYaxis()->SetTitleSize(0.05);
    cm_1_bis_h->GetXaxis()->SetLabelSize(0.05);
    cm_1_bis_h->GetYaxis()->SetLabelSize(0.05);
    //cm_1_bis_h->GetYaxis()->SetRangeUser(1.0,3e5);
    cm_1_bis_h->GetXaxis()->SetRangeUser(5.0,24);
    //cm_1_bis_h->GetYaxis()->SetRangeUser(1.0,5e1);
    //cm_1_bis_h_e->GetYaxis()->SetRangeUser(0.0,25);
        
    auto legend = new TLegend(0.55,0.75,0.85,0.85);
    string etiqueta = "Exposicion: 70 min"; 
    //legend->SetHeader("E0 * g * Ei * 1e-3","C"); // option "C" allows to center the header   etiqueta.c_str()
    TMarker *marker = new TMarker(0.1,0.1,22);
    marker->SetMarkerColor(kRed+1);
    marker->SetMarkerSize(3.0);
    TLegendEntry * entry = legend->AddEntry(marker,etiqueta.c_str(),"p");
    cm_1_bis_h->SetMarkerSize(1.0);
    legend->SetTextSize(0.05);    
    legend->SetBorderSize(1);
    legend->Draw();

}

void Enable_and_Set_Branches(TTree* & tree){
	tree->SetBranchStatus("*",0); //disable all branches
	tree->SetBranchStatus("flag",1);
	tree->SetBranchStatus("n0",1);
  	tree->SetBranchStatus("E0",1);
  	tree->SetBranchStatus("E1",1);

	tree->SetBranchAddress ("flag",&flag);
	tree->SetBranchAddress ("n0",&n0);
  	tree->SetBranchAddress ("E0",&E0);
  	tree->SetBranchAddress ("E1",&E1);
}