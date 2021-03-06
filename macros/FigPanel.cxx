// Based on 
// $ROOTSYS/tutorials/graphics/canvas2.C

#include "ZgPaperConsts.hxx"

void CanvasPartition(TCanvas *C,const Int_t Nx = 2,const Int_t Ny = 2,
                     Float_t lMargin = 0.15, Float_t rMargin = 0.05,
                     Float_t bMargin = 0.15, Float_t tMargin = 0.05);

void SetupDummy ( TH1* hFrame,
		  float xFactor, float yFactor,
		  float yaxismin, float yaxismax,
		  float xloffset, float xtoffset,
		  float xtickbase, int ndivx,
		  float yloffset, float ytoffset,
		  float ytickbase, int ndivy);

int FigPanel(
	     // --- Latest Run 6 ---
	     // TString inname="Results/TotalzgSystematics_Recut_Pp_HT54_NoEff_NoBgSub__With_AEff0_PtSmear0_ATow0_SystGeant_NoEff_NoBg_HT54_WithMisses_WithFakes_TrainedWith_Recut_McGeant_NoEff_NoBg_MB.root"
	     // --- Use this ---
	     TString inname="Results/TotalzgSystematics_ForPaper_Pp12_JP2_NoEff_NoBgSub__With_AEff0_PtSmear0_ATow0_SystGeant12_NoEff_NoBg_JP2_WithMisses_WithFakes.root"
	     // --- Different R
	     // TString inname="Results/TotalzgSystematics_R0.2_ForPaper_Pp12_JP2_NoEff_NoBgSub__With_AEff0_PtSmear0_ATow0_R0.2_SystGeant12_NoEff_NoBg_JP2_WithMisses_WithFakes_TrainedWith_R0.2_McGeant12_NoEff_NoBg_all.root"
	     // TString inname="Results/TotalzgSystematics_R0.6_ForPaper_Pp12_JP2_NoEff_NoBgSub__With_AEff0_PtSmear0_ATow0_R0.6_SystGeant12_NoEff_NoBg_JP2_WithMisses_WithFakes_TrainedWith_R0.6_McGeant12_NoEff_NoBg_all.root"
	     // Unrebinned versions
	     // --- Latest Run 6 ---
	     // TString inname="Results/TotalzgSystematics_NoRebin_Recut_Pp_HT54_NoEff_NoBgSub__With_AEff0_PtSmear0_ATow0_SystGeant_NoEff_NoBg_HT54_WithMisses_WithFakes_TrainedWith_Recut_McGeant_NoEff_NoBg_MB.root"
	     // --- Use one of these ---
	     // TString inname="Results/TotalzgSystematics_NoRebin_ForPaper_Pp12_JP2_NoEff_NoBgSub__With_AEff0_PtSmear0_ATow0_SystGeant12_NoEff_NoBg_JP2_WithMisses_WithFakes.root"
	     //// Not this one really TString inname="Results/TotalzgSystematics_NoRebin_ForPaper_Pp12_HT54_JP2_NoEff_NoBgSub__With_AEff0_PtSmear0_ATow0_SystGeant12_NoEff_NoBg_HT54_JP2_WithMisses_WithFakes.root"
	     ){
  TString plotpath="./figs/";
  
  // gROOT->Reset();
  
  gStyle->SetHistLineWidth(2);
  gStyle->SetFrameLineWidth(2);
  gStyle->SetOptStat(0);
  gStyle->SetPadBorderMode(0);
  gStyle->SetFrameBorderMode(0);

  gStyle->SetTitleX(0.1f);
  gStyle->SetTitleW(0.8f);
  gStyle->SetTitleBorderSize(0);	//Title box border thickness

  Float_t small = 1e-5; // for panel setup

  bool ShowNoHadro = true;
  bool ShowHardProbes=inname.Contains("ForPaper_Pp12_JP2") && false;
    

  // Load histos
  TFile* infile = new TFile(inname,"READ");
  TObjArray histos( 6 );
  histos.Add( infile->Get("Incunfold_1015_2") );
  histos.Add( infile->Get("Incunfold_1520_2") );
  histos.Add( infile->Get("Incunfold_2025_2") );
  histos.Add( infile->Get("Incunfold_2530_2") );
  histos.Add( infile->Get("Incunfold_3040_2") );
  histos.Add( infile->Get("Incunfold_4060_2") );

  TObjArray SysUnfold( 6 );
  SysUnfold.Add( infile->Get("SysIncunfold_1015") );
  SysUnfold.Add( infile->Get("SysIncunfold_1520") );
  SysUnfold.Add( infile->Get("SysIncunfold_2025") );
  SysUnfold.Add( infile->Get("SysIncunfold_2530") );
  SysUnfold.Add( infile->Get("SysIncunfold_3040") );
  SysUnfold.Add( infile->Get("SysIncunfold_4060") );

  TObjArray SysRest( 6 );
  SysRest.Add( infile->Get("Incunfold_1015_2_minmax") );
  SysRest.Add( infile->Get("Incunfold_1520_2_minmax") );
  SysRest.Add( infile->Get("Incunfold_2025_2_minmax") );
  SysRest.Add( infile->Get("Incunfold_2530_2_minmax") );
  SysRest.Add( infile->Get("Incunfold_3040_2_minmax") );
  SysRest.Add( infile->Get("Incunfold_4060_2_minmax") );

  bool SuppresSystematics = ( SysRest.At(0)==0 );

  // Number of PADS
  // const Int_t Nx = 2;
  // const Int_t Ny = 3;
  const Int_t Nx = 3;
  const Int_t Ny = 2;

  if (histos.GetEntries()!=Nx*Ny) {
    cerr << "Incompatible number of histos." << endl;
    return -1;
  }

  // Margins etc.
  // // Good for Nx=2, Ny=3, 300,220;
  // float lMargin = 0.10;
  // float rMargin = 0.05;
  // float bMargin = 0.08;
  // float tMargin = 0.05;
  // float xloffset=0.02;
  // float xtoffset=3;
  // int   ndivx= 505; 
  // float yloffset=0.02;
  // float ytoffset=3;
  // int   ndivy= 505; 
  // float xtickbase = 0.05;
  // float ytickbase = 0.03;
  

  // // // Good for Nx=3, Ny=2, 300,220;
  // float lMargin = 0.07;
  // float rMargin = 0.03;
  // float bMargin = 0.11;
  // float tMargin = 0.03;
  // float xloffset=0.02;
  // float xtoffset=2;
  // int   ndivx= 505; 
  // float yloffset=0.02;
  // float ytoffset=2;
  // int   ndivy= 505; 
  // float xtickbase = 0.04;
  // float ytickbase = 0.04;
  
  // // Good for Nx=3, Ny=2, 300,240;
  float lMargin = 0.07;
  float rMargin = 0.03;
  float bMargin = 0.13;
  float tMargin = 0.03;
  float xloffset=0.02;
  float xtoffset=2.2;
  int   ndivx= 505; 
  float yloffset=0.02;
  float ytoffset=1.5;
  int   ndivy= 505; 
  float xtickbase = 0.04;
  float ytickbase = 0.04;

  float legs = 20;

  // Canvas setup
  // TCanvas* C =new TCanvas("C","", Nx*300,Ny*220);
  TCanvas* C =new TCanvas("C","", Nx*300,Ny*240);
  CanvasPartition(C,Nx,Ny,lMargin,rMargin,bMargin,tMargin);
  TPad *pad[Nx][Ny];

  int histcount=0;
  
  // Set up the pads previously created.
  for (Int_t i=0;i<Nx;i++) {
    for (Int_t j=0;j<Ny;j++) {
      C->cd(0);
      char pname[16];
      sprintf(pname,"pad_%i_%i",i,j);
      pad[i][j] = (TPad*) gROOT->FindObject(pname);
      pad[i][j]->Draw();
      pad[i][j]->cd();
      gPad->SetTicky();      gPad->SetTickx();
      gPad->SetGridx(0);     gPad->SetGridy(0);
      
    }
  }

  // Load Pythia8 and Hard Probes comparison
  // TFile* fHP = new TFile( "~/BasicAj/AjResults/UnfoldedPpSystematics_Histos.root", "READ");
  TFile* fHP = new TFile( "~/BasicAj/NewAjResults/UnfoldedPpSystematics_Histos.root", "READ");

  // TFile* fP8 = new TFile( "~/BasicAj/AjResults/UnfoldedPpSystematics_Histos.root", "READ");
  // TString fP8name = "Results/CutUp_ForPaper_Pythia8_NoEff_NoBgSub.root";
  // TString fP8name = "Results/CutUp_ForPaper_Pythia8_NoEff_NoBgSub_NoHadronization.root";
  TString nP8default = "Results/CutUp_ForPaper_Pythia8_NoEff_NoBgSub.root";
  TString nP8nohadro = "Results/CutUp_ForPaper_Pythia8_NoEff_NoBgSub_NoHadronization.root";

  TString nHWdefault = "Results/CutUp_ForPaper_Herwig_NoEff_NoBgSub.root";
  TString nHWnohadro = "Results/CutUp_ForPaper_Herwig_NoEff_NoBgSub_NoHadro.root";
    
  if ( inname.Contains("R0.2") ){
    nP8default.ReplaceAll( "CutUp_ForPaper","CutUp_R0.2_ForPaper");
    nHWdefault.ReplaceAll( "CutUp_ForPaper","CutUp_R0.2_ForPaper");
    nP8nohadro.ReplaceAll( "CutUp_ForPaper","CutUp_R0.2_ForPaper");
    nHWnohadro.ReplaceAll( "CutUp_ForPaper","CutUp_R0.2_ForPaper");
  }
  if ( inname.Contains("R0.6") ){
    nP8default.ReplaceAll( "CutUp_ForPaper","CutUp_R0.6_ForPaper");
    nHWdefault.ReplaceAll( "CutUp_ForPaper","CutUp_R0.6_ForPaper");
    nP8nohadro.ReplaceAll( "CutUp_ForPaper","CutUp_R0.6_ForPaper");
    nHWnohadro.ReplaceAll( "CutUp_ForPaper","CutUp_R0.6_ForPaper");
  }
  TFile* fP8default = new TFile( nP8default , "READ");
  TFile* fHWdefault = new TFile( nHWdefault , "READ");
  TFile* fP8nohadro = new TFile( nP8nohadro , "READ");
  TFile* fHWnohadro = new TFile( nHWnohadro , "READ");

  TLatex latex;
  // latex.SetNDC();
  
  // Prep Theory curve
  bool ShowTheory=true;
  TF1* PbarQjet = new TF1("PbarQjet","1./[0] * 4./3. * ( (1+pow(x,2))/(1-x) + (1 + pow(1-x,2))/x )", 0.1, 0.5);
  PbarQjet->SetParameter( 0,4.2593);
  PbarQjet->SetLineColor(kGreen);
  
  TF1* FUVQjet = new TF1("FUVQjet", "[0]*(PbarQjet)", 0.1,0.5);
  FUVQjet->SetParameter( 0,1);

  FUVQjet->SetLineColor(kTeal+2);
  FUVQjet->SetLineWidth(2);
  FUVQjet->SetLineStyle(3);
  FUVQjet->SetParameter( 0,1);

  TLegend* leg;
  TLegend* leg2;
  TString s;
  
  // And draw. Reordered.
  // for (Int_t i=0;i<Nx;i++) {
  //   for (Int_t j=Ny-1;j>=0;j--) {
  for (Int_t j=Ny-1;j>=0;j--) {
    for (Int_t i=0;i<Nx;i++) {
      C->cd(0);
      pad[i][j]->cd();
      TH1D* h = (TH1D*) histos.At(histcount);
      TH1D* sysunfold;
      TH1D* sysrest;
      TH1D* systot;
      if ( !SuppresSystematics ){
	sysunfold = (TH1D*) SysUnfold.At(histcount);
        sysrest = (TH1D*) SysRest.At(histcount);
	systot = (TH1D*) sysrest->Clone( TString("tot")+sysrest->GetName() );
	for (int ii=1; ii<=systot->GetNbinsX() ; ++ii ){
	  systot->SetBinError (ii, sqrt( pow( sysunfold->GetBinError(ii), 2) + pow( sysrest->GetBinError(ii), 2) ));
	}
      }
	
      char hname[16];
      sprintf(hname,"dummy_%i_%i",i,j);

      TH1D* dummy = new TH1D( hname,"", 20, 0.05, 0.55);
      dummy->GetXaxis()->SetTitle(h->GetXaxis()->GetTitle());
      dummy->GetYaxis()->SetTitle(h->GetYaxis()->GetTitle());
      dummy->Reset();
      dummy->SetLineColor(0);      dummy->SetLineWidth(0);
      dummy->Draw();

      // Size factors
      Float_t xFactor = pad[0][0]->GetAbsWNDC()/pad[i][j]->GetAbsWNDC();
      Float_t yFactor = pad[0][0]->GetAbsHNDC()/pad[i][j]->GetAbsHNDC();

      // y axis range
      // float yaxismin = 0.0001;
      // float yaxismax = 1.2*h->GetMaximum();
      // float yaxismin = 0;
      float yaxismin = -0.5;
      float yaxismax = 8;
      if ( inname.Contains("NoRebin")) yaxismax = 8.5;

      SetupDummy ( dummy,
		   xFactor, yFactor,
		   yaxismin, yaxismax,
		   xloffset, xtoffset,
		   xtickbase, ndivx,
		   yloffset, ytoffset,
		   ytickbase, ndivy );

      h->SetAxisRange(0.1 + 0.001, 0.5 - 0.001);

      if ( !SuppresSystematics){
	systot->SetAxisRange(0.1 + 0.001, 0.5 - 0.001);
	systot->SetMarkerStyle(20);      systot->SetMarkerSize(0);      systot->SetLineWidth( 0 );
	systot->SetFillStyle(1001);    
	
	sysunfold->SetAxisRange(0.1 + 0.001, 0.5 - 0.001);
	sysunfold->SetMarkerStyle(20);      sysunfold->SetMarkerSize(0);      sysunfold->SetLineWidth( 0 );
	sysunfold->SetFillStyle(1001);    
	
	sysrest->SetAxisRange(0.1 + 0.001, 0.5 - 0.001);
	sysrest->SetMarkerStyle(20);      sysrest->SetMarkerSize(0);      sysrest->SetLineWidth( 0 );
	sysrest->SetFillStyle(3001);
	sysrest->SetFillColor( kGray+2 );
      }

      float ptleft=0;
      float ptright=0;

      // leg = new TLegend( 0.2, 4.4, 0.5, 6.7, "", "br" );
      // if (ShowTheory) leg = new TLegend( 0.2, 4.0, 0.5, 6.8, "", "br" );
      leg = new TLegend( 0.2, 6.5, 0.5, 7.5, "", "br" );
      
      leg->SetBorderSize(0);
      leg->SetTextFont(43);
      leg->SetTextSize(legs);
  
      leg->SetFillStyle(0);
      // leg->SetMargin(0.1);

      switch (histcount){
      case 0 :
	ptleft=10; ptright=15;	      
	break;
      case 1 :
	ptleft=15; ptright=20;
	break;
      case 2 :
	ptleft=20; ptright=25;
	break;
      case 3 :
	ptleft=25; ptright=30;
	break;	
      case 4 :
	ptleft=30; ptright=40;
	break; 
      case 5 :
	ptleft=40; ptright=60;
	break;
      default :
	cerr << "Unsupported number of histos" << endl;
	return -1;
	break; // ROOT can be stupid
      }
      h->SetMarkerStyle( zgconsts::datamark[histcount] );
      h->SetMarkerSize( zgconsts::datamarksize[histcount] );
      h->SetMarkerColor( zgconsts::datacol[histcount] );
      h->SetLineColor( zgconsts::datacol[histcount] );
      h->SetLineWidth( 2 );
      if ( !SuppresSystematics){
	sysunfold->SetFillColor( zgconsts::syscol[histcount] );
	systot->SetFillColor( zgconsts::syscol[histcount]  );
      }

      // Systematics in the back of theory
      if ( !SuppresSystematics){
	// sysunfold->Draw("9e2same");
	// sysrest->Draw("9e2same");
	// h->Draw("9E0X0same");
	systot->Draw("9e2same");
      }

      // Hard Probes
      TString name="UnfoldedNS_"; name += int(ptleft+0.01); name += "_"; name += int(ptright+0.01); name += "_minmax";
      TH1D* minmaxNS = (TH1D*) fHP->Get(name);
      // cout << " ---------------------------------> Adding " << name << endl;
      if ( minmaxNS && ShowHardProbes ){
	minmaxNS->SetLineWidth( 0 );
	minmaxNS->SetFillStyle(1001);
	minmaxNS->SetFillColor( kRed-10 );
	minmaxNS->SetLineColor(kRed-10);
	minmaxNS->SetMarkerColor(kRed);
	minmaxNS->SetMarkerStyle(29);
	minmaxNS->SetMarkerSize(2);
	minmaxNS->SetAxisRange(0.11, 0.49);
	minmaxNS->Draw("9E2same");
	minmaxNS->Draw("9same");
	leg->AddEntry(minmaxNS->GetName(), "HP Result");
      } 
            
      name = "p8_Incmeas_"; name += int(ptleft+0.01); name += int(ptright+0.01);
      // name = "AS_P8_SoftJets_MB_"; name += int(ptleft+0.01); name+="_"; name += int(ptright+0.01);
      TH1D* hP8 = (TH1D*) fP8default->Get(name);
      if ( hP8 ){
	// hP8->SetLineStyle(1);
	hP8->SetAxisRange(0.11, 0.49);
	hP8->SetLineColor( kBlack );
	hP8->SetLineWidth( 2 );
	hP8->SetLineStyle( 1 );
	hP8->Draw("9lhist][same");
	// if ( !ShowHardProbes) leg->AddEntry(hP8->GetName(), "Pythia8","l");
      }

      TH1D* hHW = (TH1D*) fHWdefault->Get(name);
      if ( hHW ){
	hHW->SetName(TString(hHW->GetName())+"_herwig");
	// hHW->SetLineStyle(1);
	hHW->SetAxisRange(0.11, 0.49);
	hHW->SetLineColor( kRed );
	hHW->SetLineWidth( 4 );
	hHW->SetLineStyle( 1 );
	hHW->Draw("9lhist][same");
	// if ( !ShowHardProbes) leg->AddEntry(hHW->GetName(), "Pythia8","l");
      }

      TH1D* hP8nohadro = (TH1D*) fP8nohadro->Get(name);
      if ( hP8 && ShowNoHadro ){
	hP8nohadro->SetName(TString(hP8nohadro->GetName())+"_nohadro");
	hP8nohadro->SetAxisRange(0.11, 0.49);
	hP8nohadro->SetLineColor( kGray+2 );
	hP8nohadro->SetLineWidth( 3 );
	hP8nohadro->SetLineStyle( 2 );
	hP8nohadro->Draw("9lhist][same");
	// leg->AddEntry(hP8nohadro->GetName(), "Pythia8 NoHadro","l");
      }

      TH1D* hHWnohadro = (TH1D*) fHWnohadro->Get(name);
      if ( hHW && ShowNoHadro ){
	hHWnohadro->SetName(TString(hHWnohadro->GetName())+"_herwig_nohadro");
	hHWnohadro->SetAxisRange(0.11, 0.49);
	hHWnohadro->SetLineColor( kRed );
	hHWnohadro->SetLineWidth( 3 );
	hHWnohadro->SetLineStyle( 2 );
	hHWnohadro->Draw("9lhist][same");
	// leg->AddEntry(hHWnohadro->GetName(), "Pythia8 NoHadro","l");
      }

      if (ShowTheory) {
	FUVQjet->Draw("same");
	// leg->AddEntry( FUVQjet, "F_{UV}^{q}","l");
      }

      // // Systematics in the back of theory
      // if ( !SuppresSystematics){
      // 	// sysunfold->Draw("9e2same");
      // 	// sysrest->Draw("9e2same");
      // 	// h->Draw("9E0X0same");
      // 	systot->Draw("9e2same");
      // }

      // Data in the front
      // -----------------
      h->Draw("9same");
      s="p_{T}="; s+=int(ptleft); s+="-"; s+=int(ptright); s+=" GeV/c";
      leg->AddEntry(h->GetName(), s,"lp");

      
      leg->Draw();

      latex.SetTextColor( kAzure-6 );      latex.SetTextSize(0.07*yFactor);
      latex.SetTextFont( 62 ); // 42: helvetica, 62: helvetica bold
      latex.DrawLatex( .1,1, "STAR");
      
      if ( histcount==3 ){
	leg2 = new TLegend( 0.15, 4.0, 0.5, 6.0, "", "br" );
	leg2->SetBorderSize(0);
	leg2->SetTextFont(63);
	leg2->SetTextSize(legs*0.8);
	leg2->SetFillStyle(0);
	leg2->AddEntry((TObject*)0, "p+p, #sqrt{s}=200 GeV", "");
	s = "anti-k_{T}, R=0.4";
	if ( inname.Contains("R0.2") ) s = "anti-k_{T}, R=0.2";
	if ( inname.Contains("R0.6") ) s = "anti-k_{T}, R=0.6";
	    
	leg2->AddEntry((TObject*)0, s, "");
	leg2->Draw();
      }
	
      if ( histcount==1 ){
	leg2 = new TLegend( 0.2, 4.5, 0.5, 6.5, "", "br" );
	leg2->SetBorderSize(0);
	leg2->SetTextFont(43);
	leg2->SetTextSize(legs);
	leg2->SetFillStyle(0);

	if ( hP8 ){
	  leg2->AddEntry(hP8->GetName(), "Pythia8","l");
	  if ( hP8nohadro && ShowNoHadro ){
	    leg2->AddEntry(hP8nohadro->GetName(), "Pythia8 NoHadro","l");
	  }
	  leg2->Draw();
	}
      } 

      if ( histcount==2 ){
	leg2 = new TLegend( 0.2, 4.5, 0.5, 6.5, "", "br" );
	leg2->SetBorderSize(0);
	leg2->SetTextFont(43);
	leg2->SetTextSize(legs);
	leg2->SetFillStyle(0);

	if ( hHW ){
	  leg2->AddEntry(hHW->GetName(), "Herwig","l");
	  if ( hHWnohadro && ShowNoHadro ){
	    leg2->AddEntry(hHWnohadro->GetName(), "Herwig NoHadro","l");
	  }

	  leg2->Draw();
	}
      } 

      if ( histcount==0 ){
	leg2 = new TLegend( 0.2, 4.5, 0.5, 6.5, "", "br" );
	leg2->SetBorderSize(0);
	leg2->SetTextFont(43);
	leg2->SetTextSize(legs);
	leg2->SetFillStyle(0);

	if (ShowTheory) {
	  leg2->AddEntry( FUVQjet, "F_{UV}^{q}","l");
	  leg2->Draw();
	}	
      }

      cout << "Percentage in 0 bin:" << endl;
      cout << s << endl;
      cout << setprecision(2);
      cout << "Data:        " << 100*h->GetBinContent(1) / h->Integral(1,h->GetNbinsX()) << " %" << endl;
      cout << "pythia:      " << 100*hP8->GetBinContent(1) / hP8->Integral(1,hP8->GetNbinsX()) << " %" <<  endl;
      cout << "herwig:      " << 100*hHW->GetBinContent(1) / hHW->Integral(1,hHW->GetNbinsX()) << " %" <<  endl;
      cout << setprecision(4);
      if ( hP8nohadro )
	cout << "p8 no hadro: " << 100*hP8nohadro->GetBinContent(1) / hP8nohadro->Integral(1,hP8nohadro->GetNbinsX()) << " %" <<  endl;
      if ( hHWnohadro )
	cout << "hw no hadro: " << 100*hHWnohadro->GetBinContent(1) / hHWnohadro->Integral(1,hHWnohadro->GetNbinsX()) << " %" <<  endl;
      cout << " ############################# " << endl;
	    
      histcount++; 
    }    
  }
      


  C->cd();  
  // C->SaveAs(plotpath+"delme.pdf");
  // C->SaveAs(plotpath+"delme2.pdf");
  
  TString plotname=gSystem->BaseName(inname);
  plotname.Prepend(plotpath+"FigPanel_");
  C->SaveAs(plotname + ".pdf");




  return 0;
}

// -----------------------------------------------------------------------------


void CanvasPartition(TCanvas *C,const Int_t Nx,const Int_t Ny,
                     Float_t lMargin, Float_t rMargin,
                     Float_t bMargin, Float_t tMargin)
{
  if (!C) return;

  // Setup Pad layout:
  Float_t vSpacing = 0.0;
  Float_t vStep  = (1.- bMargin - tMargin - (Ny-1) * vSpacing) / Ny;

  Float_t hSpacing = 0.0;
  Float_t hStep  = (1.- lMargin - rMargin - (Nx-1) * hSpacing) / Nx;

  Float_t vposd,vposu,vmard,vmaru,vfactor;
  Float_t hposl,hposr,hmarl,hmarr,hfactor;

  for (Int_t i=0;i<Nx;i++) {

    if (i==0) {
      hposl = 0.0;
      hposr = lMargin + hStep;
      hfactor = hposr-hposl;
      hmarl = lMargin / hfactor;
      hmarr = 0.0;
    } else if (i == Nx-1) {
      hposl = hposr + hSpacing;
      hposr = hposl + hStep + rMargin;
      hfactor = hposr-hposl;
      hmarl = 0.0;
      hmarr = rMargin / (hposr-hposl);
    } else {
      hposl = hposr + hSpacing;
      hposr = hposl + hStep;
      hfactor = hposr-hposl;
      hmarl = 0.0;
      hmarr = 0.0;
    }

    for (Int_t j=0;j<Ny;j++) {

      if (j==0) {
	vposd = 0.0;
	vposu = bMargin + vStep;
	vfactor = vposu-vposd;
	vmard = bMargin / vfactor;
	vmaru = 0.0;
      } else if (j == Ny-1) {
	vposd = vposu + vSpacing;
	vposu = vposd + vStep + tMargin;
	vfactor = vposu-vposd;
	vmard = 0.0;
	vmaru = tMargin / (vposu-vposd);
      } else {
	vposd = vposu + vSpacing;
	vposu = vposd + vStep;
	vfactor = vposu-vposd;
	vmard = 0.0;
	vmaru = 0.0;
      }

      C->cd(0);

      char name[16];
      sprintf(name,"pad_%i_%i",i,j);
      TPad *pad = (TPad*) gROOT->FindObject(name);
      if (pad) delete pad;
      pad = new TPad(name,"",hposl,vposd,hposr,vposu);
      pad->SetLeftMargin(hmarl);
      pad->SetRightMargin(hmarr);
      pad->SetBottomMargin(vmard);
      pad->SetTopMargin(vmaru);

      pad->SetFrameBorderMode(0);
      pad->SetBorderMode(0);
      pad->SetBorderSize(0);

      pad->Draw();
    }
  }
}

// -----------------------------------------------------------------------------
void SetupDummy ( TH1* hFrame,
		  float xFactor, float yFactor,
		  float yaxismin, float yaxismax,
		  float xloffset, float xtoffset,
		  float xtickbase, int ndivx,
		  float yloffset, float ytoffset,
		  float ytickbase, int ndivy
		  )
{
  // y axis range
  hFrame->GetYaxis()->SetRangeUser(yaxismin,yaxismax);
  float ls = 20;
  float ts = 20;
  
  // Format for x axis
  hFrame->GetXaxis()->SetLabelFont(43);
  hFrame->GetXaxis()->SetLabelSize(ls);
  hFrame->GetXaxis()->SetLabelOffset(xloffset);
  hFrame->GetXaxis()->SetTitleFont(43);
  hFrame->GetXaxis()->SetTitleSize(ts);
  hFrame->GetXaxis()->SetTitleOffset(xtoffset);
  hFrame->GetXaxis()->CenterTitle( true );
  hFrame->GetXaxis()->SetNdivisions(ndivx);
  
  // TICKS X Axis
  hFrame->GetXaxis()->SetTickLength(yFactor*xtickbase/xFactor);
  
  // Format for y axis
  hFrame->GetYaxis()->SetLabelFont(43);
  hFrame->GetYaxis()->SetLabelSize(ls);
  hFrame->GetYaxis()->SetLabelOffset(yloffset);
  hFrame->GetYaxis()->SetTitleFont(43);
  hFrame->GetYaxis()->SetTitleSize(ls);
  hFrame->GetYaxis()->SetTitleOffset(ytoffset);
  
  hFrame->GetYaxis()->CenterTitle( true );
  hFrame->GetYaxis()->SetNdivisions(ndivy);
  
  // TICKS Y Axis
  hFrame->GetYaxis()->SetTickLength(xFactor*ytickbase/yFactor);      
}

