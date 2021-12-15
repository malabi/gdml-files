//////////////////////////////////////////////////////////////////
/// This class handles the placement of ancillary detectors
/// in AGATA. Each ancillary detector should be described in
/// a different class inheriting from AgataAncillaryScheme
/// and providing concrete implementation of the pure virtual
/// methods (of AgataAncillaryScheme and AgataDetectorConstructed)
/// User should describe his own ancillary!!!!
/////////////////////////////////////////////////////////////////

#include "AgataDetectorAncillary.hh"
#include <dlfcn.h>

/// User ancillary class should be included here!
#ifdef GASP
#include "AgataAncillaryEuclides.hh"
#else
#ifdef CLARA
#include "AgataAncillaryMcp.hh"
#else
#ifdef POLAR
#include "AgataAncillaryScatterer.hh"
#else
#ifdef EUCLIDES
#include "AgataAncillaryEuclides.hh"
#else
#include "AgataAncillaryShell.hh"
#include "AgataAncillaryKoeln.hh"
#include "AgataAncillaryMcp.hh"
#include "AgataAncillaryADCA.hh"
#ifdef ANCIL
#include "AgataAncillaryEuclides.hh"
#include "AgataAncillaryNeutronWall.hh"
#include "AgataAncillaryRFD.hh"
#include "AgataAncillaryBrick.hh"
#include "AgataAncillaryHelena.hh"
#include "AgataAncillaryDiamant.hh"
#include "AgataAncillaryAida.hh"
#include "AgataAncillaryCassandra.hh"
#include "AgataAncillaryNDet.hh"
#include "AgataAncillaryNordBallNDet.hh"
#include "AgataAncillaryExogam.hh"
#include "AgataAncillaryFatima.hh"
#include "AgataAncillaryGSIChambRing.hh"
#include "AgataAncillarySpider.hh"
#include "OrsayPlastic.hh"
#include "AgataAncillaryOups.hh"
#include "GalileoPlunger.hh"
#include "AgataAncillaryParis.hh"
#include "AgataAncillaryLycca.hh"
#include "AgataAncillaryNeda.hh"
#include "AgataAncillaryHC.hh"
#include "AgataAncillaryGanilChamb.hh"
#include "AgataAncillaryDiamant_FP.hh"
#include "AgataAncillaryDiamant_FTgt.hh"
#include "AgataAncillaryLNLChamb.hh"
#include "AgataAncillaryLNLGRIT.hh"

//#include "AgataAncillarySigma.hh"
#endif
#endif
#endif
#endif
#endif


#ifdef MINIBALL
#include "Miniball.hh"
#endif

using namespace std;

std::vector<void*> AgataDetectorAncillary::AddOns;

#ifdef GASP

AgataDetectorAncillary::AgataDetectorAncillary( G4int type, G4String path, G4String name )
{
  numAnc = 1;
  minOffset = 3000;
  // pointers to the ancillary detector classes
  theEuclides = new AgataAncillaryEuclides(path,name);
  theAncillary.push_back((AgataAncillaryScheme*)    theEuclides);
  theConstructed.push_back((AgataDetectorConstructed*)theEuclides);
}

AgataDetectorAncillary::AgataDetectorAncillary( G4String type, G4String path, G4String name )
{
  numAnc = 1;
  minOffset = 3000;

  // pointers to the ancillary detector classes
  theEuclides = new AgataAncillaryEuclides(path,name);
  theAncillary.push_back((AgataAncillaryScheme*)    theEuclides);
  theConstructed.push_back((AgataDetectorConstructed*)theEuclides);
}
#else

#ifdef CLARA
AgataDetectorAncillary::AgataDetectorAncillary( G4int type, G4String path, G4String name )
{
  numAnc = 1;
  minOffset = 1000;

  // pointers to the ancillary detector classes
  theMcp = new AgataAncillaryMcp(path,name);
  theAncillary.push_back((AgataAncillaryScheme*)    theMcp);
  theConstructed.push_back((AgataDetectorConstructed*)theMcp);
}

AgataDetectorAncillary::AgataDetectorAncillary( G4String type, G4String path, G4String name )
{
  numAnc = 1;
  minOffset = 1000;

  // pointers to the ancillary detector classes
  theMcp = new AgataAncillaryMcp(path,name);
  theAncillary.push_back((AgataAncillaryScheme*)    theMcp);
  theConstructed.push_back((AgataDetectorConstructed*)theMcp);
}
#else
#ifdef POLAR
AgataDetectorAncillary::AgataDetectorAncillary( G4int type, G4String path )
{
  numAnc = 1;
  minOffset = 0;
  // pointers to the ancillary detector classes
  AgataAncillaryScatterer* theScatterer = new AgataAncillaryScatterer(path);
  theAncillary.push_back((AgataAncillaryScheme*)    theScatterer);
  theConstructed.push_back((AgataDetectorConstructed*)theScatterer);
}

AgataDetectorAncillary::AgataDetectorAncillary( G4String type, G4String path )
{
  numAnc = 1;
  minOffset = 0;

  // pointers to the ancillary detector classes
  AgataAncillaryScatterer* theScatterer = new AgataAncillaryScatterer(path);
  theAncillary.push_back((AgataAncillaryScheme*)    theScatterer);
  theConstructed.push_back((AgataDetectorConstructed*)theScatterer);
}
#else
#ifdef EUCLIDES
AgataDetectorAncillary::AgataDetectorAncillary( G4int type, G4String path )
{
  numAnc = 1;
  minOffset = 0;

  // pointers to the ancillary detector classes
  theEuclides = new AgataAncillaryEuclides(path);
  theAncillary.push_back((AgataAncillaryScheme*)    theEuclides);
  theConstructed.push_back((AgataDetectorConstructed*)theEuclides);
}

AgataDetectorAncillary::AgataDetectorAncillary( G4String type, G4String path )
{
  numAnc = 1;
  minOffset = 0;

  // pointers to the ancillary detector classes
  theEuclides = new AgataAncillaryEuclides(path);
  theAncillary  [0] = (AgataAncillaryScheme*)    theEuclides;
  theConstructed[0] = (AgataDetectorConstructed*)theEuclides;
}

#else

AgataDetectorAncillary::AgataDetectorAncillary( G4int type, G4String path, G4String name )
{
  numAnc = 1;
#ifdef ANTIC
  minOffset = 1000;
#else
  minOffset = 0;
#endif

  // pointers to the ancillary detector classes
  AgataAncillaryKoeln*    theKoeln    = NULL;
//  AgataAncillaryADCA*     theADCA     = NULL;  // Commented as already defined in the include
  AgataAncillaryMcp*      theMcp      = NULL;
  AgataAncillaryShell*    theShell    = NULL;
#ifdef ANCIL
  AgataAncillaryEuclides*     theEuclides     = NULL;
  AgataAncillaryNeutronWall*  theNWall        = NULL;
  AgataAncillaryNeda*         theNeda         = NULL;
  AgataAncillaryRFD*          theRFD          = NULL;
  AgataAncillaryBrick*        theBrick        = NULL;
  AgataAncillaryHelena*       theHelena       = NULL;
  AgataAncillaryDiamant*      theDiamant      = NULL;
  AgataAncillaryAida*         theAida         = NULL;
  AgataAncillaryCassandra*    theCassandra    = NULL;
  AgataAncillaryNDet*         theNDet         = NULL;
  AgataAncillaryNordBallNDet* theNordBallNDet = NULL;
  AgataAncillaryExogam*       theExogam       = NULL;
  AgataAncillaryFatima*       theFatima       = NULL;
  AgataAncillaryParis*        theParis        = NULL;
  AgataAncillaryGSIChambRing* theGSIChambRing = NULL;
  AgataAncillarySpider*       theSpider       = NULL;
  OrsayPlastic*               theOrsayPlastic = NULL;
  GalileoPlunger*             theGalileoPlunger = NULL;
  AgataAncillaryOups*         theOups         = NULL;
  AgataAncillaryLycca*        theLycca        = NULL;
  AgataAncillaryHC*           theHC    	      = NULL;
  AgataAncillaryGanilChamb*   theGanilChamb   = NULL;
  AgataAncillaryDiamant_FP*   theDiamPlung    = NULL;
  AgataAncillaryDiamant_FTgt* theDiamFTgt    = NULL;
  AgataAncillaryLNLChamb*     theLNLChamb  = NULL;
  AgataAncillaryLNLGRIT*     theLNLGRIT  = NULL;

//  AgataAncillarySigma*       theSigma       = NULL;
#ifdef MINIBALL
  Miniball*              theMiniball = NULL;
#endif
#endif 

  switch(type)
    {
    case 0: // empty
      break;
    case 1:
      theKoeln       = new AgataAncillaryKoeln(path,name);
      theAncillary.push_back((AgataAncillaryScheme*)    theKoeln);
      theConstructed.push_back((AgataDetectorConstructed*)theKoeln);
      break;
    case 2:
      theShell       = new AgataAncillaryShell(path,name);
      theAncillary.push_back((AgataAncillaryScheme*)    theShell);
      theConstructed.push_back((AgataDetectorConstructed*)theShell);
      break;
    case 3:
      theMcp         = new AgataAncillaryMcp(path,name);
      theAncillary.push_back((AgataAncillaryScheme*)    theMcp);
      theConstructed.push_back((AgataDetectorConstructed*)theMcp);
      break;
#ifdef ANCIL
    case 4:
      theEuclides    = new AgataAncillaryEuclides(path,name);
      theAncillary.push_back((AgataAncillaryScheme*)    theEuclides);
      theConstructed.push_back((AgataDetectorConstructed*)theEuclides);
      break;
    case 5: // empty->ADCA
      theADCA = new AgataAncillaryADCA(path,name);
      theAncillary.push_back((AgataAncillaryScheme*)    theADCA);
      theConstructed.push_back((AgataDetectorConstructed*)theADCA);
      break;
    case 6: 
      theBrick          = new AgataAncillaryBrick(path,name);
      theAncillary.push_back((AgataAncillaryScheme*)    theBrick);
      theConstructed.push_back((AgataDetectorConstructed*)theBrick);
      break;
    case 7:
      theNWall       = new AgataAncillaryNeutronWall(path,name);
      theAncillary.push_back((AgataAncillaryScheme*)    theNWall);
      theConstructed.push_back((AgataDetectorConstructed*)theNWall);
      break;
    case 8:  // Diamant
      theDiamant        = new AgataAncillaryDiamant(path,name);
      theAncillary.push_back((AgataAncillaryScheme*)    theDiamant);
      theConstructed.push_back((AgataDetectorConstructed*)theDiamant);
      break;
    case 9:  // Exogam
      theExogam         = new AgataAncillaryExogam(path,name);
      theAncillary.push_back((AgataAncillaryScheme*)    theExogam);
      theConstructed.push_back((AgataDetectorConstructed*)theExogam);
      break;
    case 10:
      theHelena         = new AgataAncillaryHelena(path,name);
      theAncillary.push_back((AgataAncillaryScheme*)    theHelena);
      theConstructed.push_back((AgataDetectorConstructed*)theHelena);
      break;
    case 11:
      theRFD             = new AgataAncillaryRFD(path,name);
      theAncillary.push_back((AgataAncillaryScheme*)    theRFD);
      theConstructed.push_back((AgataDetectorConstructed*)theRFD);
      break;
    case 12:
      theNeda            = new AgataAncillaryNeda(path,name);
      theAncillary.push_back((AgataAncillaryScheme*)theNeda);
      theConstructed.push_back((AgataDetectorConstructed*)theNeda);
      break;
      //    case 12:  // Trace (2 SD instances)
      //      break;
      //    case 14:  // cup
      //      break;
      //    case 15:  // GASPARD
      //      break;
    case 16:  // Cassandra
      theCassandra      = new AgataAncillaryCassandra(path,name);
      theAncillary.push_back((AgataAncillaryScheme*)    theCassandra);
      theConstructed.push_back((AgataDetectorConstructed*)theCassandra);
      break;
    case 17:  // AIDA
      theAida           = new AgataAncillaryAida(path,name);
      theAncillary.push_back((AgataAncillaryScheme*)    theAida);
      theConstructed.push_back((AgataDetectorConstructed*)theAida);
      break;
    case 18:  // FATIMA
      theFatima          = new AgataAncillaryFatima(path,name);
      theAncillary.push_back((AgataAncillaryScheme*)    theFatima);
      theConstructed.push_back((AgataDetectorConstructed*)theFatima);
      break;
    case 19:  // PARIS
      theParis          = new AgataAncillaryParis(path,name);
      theAncillary.push_back((AgataAncillaryScheme*)    theParis);
      theConstructed.push_back((AgataDetectorConstructed*)theParis);
      break;

    case 20:  // GSI Chamber Central Ring used in source calibration/efficiecny runs
      theGSIChambRing          = new AgataAncillaryGSIChambRing(path,name);
      theAncillary.push_back((AgataAncillaryScheme*)    theGSIChambRing);
      theConstructed.push_back((AgataDetectorConstructed*)theGSIChambRing);
      break;
    case 21: // SPIDER FROM LNL 7 trapezoidal Si with support
      theSpider           = new AgataAncillarySpider(path,name);
      theAncillary.push_back((AgataAncillaryScheme*)    theSpider);
      theConstructed.push_back((AgataDetectorConstructed*)theSpider);
      break;
    case 22:  // Lycca
      theLycca           = new AgataAncillaryLycca(path,name);
      theAncillary  [0] = (AgataAncillaryScheme*)    theLycca;
      theConstructed[0] = (AgataDetectorConstructed*)theLycca;
      break; 

    case 66:// GJ neutron devices
      theNDet            = new AgataAncillaryNDet(path,name);
      theAncillary.push_back((AgataAncillaryScheme*)    theNDet);
      theConstructed.push_back((AgataDetectorConstructed*)theNDet);
      break;
    case 23:
      theNordBallNDet   = new AgataAncillaryNordBallNDet(path,name);
      theAncillary.push_back((AgataAncillaryScheme*)    theNordBallNDet);
      theConstructed.push_back((AgataDetectorConstructed*)theNordBallNDet);
      break;
    case 24:  // Orsay Plastic
      theOrsayPlastic            = new OrsayPlastic(path,name);
      theAncillary.push_back((AgataAncillaryScheme*)    theOrsayPlastic);
      theConstructed.push_back((AgataDetectorConstructed*)theOrsayPlastic);
      break;
#ifdef MINIBALL
    case 25: //Miniball
      theMiniball = new Miniball();
      theAncillary.push_back((AgataAncillaryScheme*)    theMiniball);
      theConstructed.push_back((AgataDetectorConstructed*)theMiniball);
      break;   
#endif

    case 26:  // HoneyComb
      theHC         = new AgataAncillaryHC(path,name);
      theAncillary.push_back((AgataAncillaryScheme*)    theHC);
      theConstructed.push_back((AgataDetectorConstructed*)theHC);
      break;
    case 27:  // Ganil Vamos Chamber
      theGanilChamb         = new AgataAncillaryGanilChamb(path,name);
      theAncillary.push_back((AgataAncillaryScheme*)    theGanilChamb);
      theConstructed.push_back((AgataDetectorConstructed*)theGanilChamb);
      break;
    case 28: //Oups
      theOups = new AgataAncillaryOups(path,name);
      theAncillary.push_back((AgataAncillaryScheme*)    theOups);
      theConstructed.push_back((AgataDetectorConstructed*)theOups);
      break;
    case 29:  // Galileo Plunger
      theGalileoPlunger            = new GalileoPlunger(path,name);
      theAncillary.push_back((AgataAncillaryScheme*)    theGalileoPlunger);
      theConstructed.push_back((AgataDetectorConstructed*)theGalileoPlunger);
      break;
      
/*	case 30:  // SIGMA
	theSigma         = new AgataAncillarySigma(path,name);
	theAncillary.push_back((AgataAncillaryScheme*)    theSigma);
	theConstructed.push_back((AgataDetectorConstructed*)theSigma);
	break;
*/            
   case 31:  // Diamant Plunger
      theDiamPlung            = new AgataAncillaryDiamant_FP(path,name);
      theAncillary.push_back((AgataAncillaryScheme*)    theDiamPlung);
      theConstructed.push_back((AgataDetectorConstructed*)theDiamPlung);
      break;
   case 32:  // Diamant Plunger
      theDiamFTgt            = new AgataAncillaryDiamant_FTgt(path,name);
      theAncillary.push_back((AgataAncillaryScheme*)    theDiamFTgt);
      theConstructed.push_back((AgataDetectorConstructed*)theDiamFTgt);
      break;
   case 35:  // LNL Chamber
      theLNLChamb            = new AgataAncillaryLNLChamb(path,name);
      theAncillary.push_back((AgataAncillaryScheme*)    theLNLChamb);
      theConstructed.push_back((AgataDetectorConstructed*)theLNLChamb);
      break;
   case 36:  // LNL GRIT
      theLNLGRIT            = new AgataAncillaryLNLGRIT(path,name);
      theAncillary.push_back((AgataAncillaryScheme*)    theLNLGRIT);
      theConstructed.push_back((AgataDetectorConstructed*)theLNLGRIT);
      break;


#endif

    default:
      numAnc--;
      break;

    // default:
    //   theShell       = new AgataAncillaryShell(path,name);
    //   theAncillary.push_back((AgataAncillaryScheme*)    theShell);
    //   theConstructed.push_back((AgataDetectorConstructed*)theShell);
    //   break;
    }
  //Here we should check for addons...
  std::vector<void*>::iterator itAddOns = AddOns.begin();
  void*(*Constructor)(G4String,G4String);
  for(; itAddOns!=AddOns.end(); ++itAddOns){
    Constructor=(void*(*)(G4String,G4String))dlsym(*itAddOns,"Constructor");
    char *errormsg = dlerror();
    if(errormsg) {
      printf("dlsym %s" , errormsg);
      exit(0);
    }
    if(Constructor){
      AgataAncillaryScheme *anc = static_cast<AgataAncillaryScheme*>
	(Constructor(path,name));
      numAnc++;
      if(numAnc==whichAnc.size()){
	whichAnc[numAnc-1]=1000000+numAnc;
	theAncillary[numAnc-1]=(AgataAncillaryScheme*)anc;
	theConstructed[numAnc-1]=(AgataDetectorConstructed*)anc;
      } else {
	whichAnc.push_back(1000000+numAnc);
	theAncillary.push_back((AgataAncillaryScheme*)anc);
	theConstructed.push_back((AgataDetectorConstructed*)anc);
      }
    }
  }
}




AgataDetectorAncillary::AgataDetectorAncillary( G4String type, G4String path, G4String name )
{
  /////////////////////////////////////////
  /// Decode the "type" string
  ///////////////////////////////////////
  G4int    position = 0;
  G4int ii;
  G4String aType = type;
  G4int length = aType.length();
  
#ifdef ANTIC
  minOffset = 1000;
#else
  minOffset = 0;
#endif
  //> how many ancillaries
  sscanf( aType.c_str(), "%d", &numAnc );
  //> allocate vectors
  whichAnc.resize(numAnc);
  theAncillary.resize(numAnc);
  theConstructed.resize(numAnc);
  
  //> strip first number
  if( aType.find(" ", position) != string::npos ) {
    position = aType.find(" ", position);
    aType = aType.substr(position, length);
  }  

  // pointers to the ancillary detector classes
  AgataAncillaryKoeln*    theKoeln    = NULL;
  //AgataAncillaryADCA*    theADCA    = NULL;  // Commented as already defined in the include
  AgataAncillaryMcp*      theMcp      = NULL;
  AgataAncillaryShell*    theShell    = NULL;
#ifdef ANCIL
  AgataAncillaryEuclides*     theEuclides       = NULL;
  AgataAncillaryNeutronWall*  theNWall          = NULL;
  AgataAncillaryNeda*         theNeda           = NULL;
  AgataAncillaryRFD*          theRFD            = NULL;
  AgataAncillaryBrick*        theBrick          = NULL;
  AgataAncillaryHelena*       theHelena         = NULL;
  AgataAncillaryDiamant*      theDiamant        = NULL;
  AgataAncillaryAida*         theAida           = NULL;
  AgataAncillaryCassandra*    theCassandra      = NULL;
  AgataAncillaryNDet*         theNDet           = NULL;
  AgataAncillaryNordBallNDet* theNordBallNDet   = NULL;
  AgataAncillaryExogam*       theExogam         = NULL;
  AgataAncillaryFatima*       theFatima         = NULL;
  AgataAncillaryParis*        theParis          = NULL;
  AgataAncillaryGSIChambRing* theGSIChambRing   = NULL;
  AgataAncillarySpider*       theSpider         = NULL; 
  OrsayPlastic*               theOrsayPlastic   = NULL;
  GalileoPlunger*             theGalileoPlunger = NULL;
  AgataAncillaryOups*         theOups         = NULL;
  AgataAncillaryLycca*        theLycca          = NULL;
  AgataAncillaryHC*           theHC             = NULL;
  AgataAncillaryGanilChamb*   theGanilChamb     = NULL;
  AgataAncillaryDiamant_FP*   theDiamPlung      = NULL;
  AgataAncillaryDiamant_FTgt* theDiamFTgt       = NULL;
  AgataAncillaryLNLChamb*     theLNLChamb  = NULL;
  AgataAncillaryLNLGRIT*     theLNLGRIT  = NULL;

//  AgataAncillarySigma*       theSigma       = NULL;

#ifdef MINIBALL
  Miniball*              theMiniball = NULL;
#endif
#endif 

  for( ii=0; ii<numAnc; ii++ ) {
    //> which ancillary
    sscanf( aType.c_str(), "%d", &whichAnc[ii] );
    switch(whichAnc[ii])
      {
      case 0: // empty
	break;
      case 1:
	theKoeln       = new AgataAncillaryKoeln(path,name);
	theAncillary  [ii] = (AgataAncillaryScheme*)    theKoeln;
	theConstructed[ii] = (AgataDetectorConstructed*)theKoeln;
	break;
      case 2:
	theShell       = new AgataAncillaryShell(path,name);
	theAncillary  [ii] = (AgataAncillaryScheme*)    theShell;
	theConstructed[ii] = (AgataDetectorConstructed*)theShell;
	break;
      case 3:
	theMcp         = new AgataAncillaryMcp(path,name);
	theAncillary  [ii] = (AgataAncillaryScheme*)    theMcp;
	theConstructed[ii] = (AgataDetectorConstructed*)theMcp;
	break;
#ifdef ANCIL
      case 4:
	theEuclides    = new AgataAncillaryEuclides(path,name);
	theAncillary  [ii] = (AgataAncillaryScheme*)    theEuclides;
	theConstructed[ii] = (AgataDetectorConstructed*)theEuclides;
	break;
      case 5: // empty->ADCA
	theADCA = new AgataAncillaryADCA(path,name);
	theAncillary  [0] = (AgataAncillaryScheme*)    theADCA;
	theConstructed[0] = (AgataDetectorConstructed*)theADCA;
	break;
      case 6: 
	theBrick          = new AgataAncillaryBrick(path,name);
	theAncillary  [ii] = (AgataAncillaryScheme*)    theBrick;
	theConstructed[ii] = (AgataDetectorConstructed*)theBrick;
	break;
      case 7:
	theNWall       = new AgataAncillaryNeutronWall(path,name);
	theAncillary  [ii] = (AgataAncillaryScheme*)    theNWall;
	theConstructed[ii] = (AgataDetectorConstructed*)theNWall;
	break;
      case 8:  // Diamant
	theDiamant         = new AgataAncillaryDiamant(path,name);
	theAncillary  [ii] = (AgataAncillaryScheme*)    theDiamant;
	theConstructed[ii] = (AgataDetectorConstructed*)theDiamant;
	break;
      case 9:  // Exogam
        theExogam          = new AgataAncillaryExogam(path,name);
        theAncillary  [ii] = (AgataAncillaryScheme*)    theExogam;
        theConstructed[ii] = (AgataDetectorConstructed*)theExogam;
 	break;
      case 10:
	theHelena         = new AgataAncillaryHelena(path,name);
	theAncillary  [ii] = (AgataAncillaryScheme*)    theHelena;
	theConstructed[ii] = (AgataDetectorConstructed*)theHelena;
	break;
      case 11:
	theRFD             = new AgataAncillaryRFD(path,name);
	theAncillary  [ii] = (AgataAncillaryScheme*)    theRFD;
	theConstructed[ii] = (AgataDetectorConstructed*)theRFD;
	break;
      case 12:
	theNeda            = new AgataAncillaryNeda(path,name);
	theAncillary  [ii] = (AgataAncillaryScheme*)    theNeda;
	theConstructed[ii] = (AgataDetectorConstructed*)theNeda;
	break;
	//      case 12:  // Trace (2 SD instances)
	//	break;
	//      case 14:  // cup
	//	break;
	//      case 15:  // Gaspard
	//	break;
      case 16:  // Cassandra
	theCassandra       = new AgataAncillaryCassandra(path,name);
	theAncillary  [ii] = (AgataAncillaryScheme*)    theCassandra;
	theConstructed[ii] = (AgataDetectorConstructed*)theCassandra;
	break;
      case 17:  // AIDA
      	theAida            = new AgataAncillaryAida(path,name);
	theAncillary  [ii] = (AgataAncillaryScheme*)    theAida;
	theConstructed[ii] = (AgataDetectorConstructed*)theAida;
 	break;
      case 18:  // FATIMA
        theFatima          = new AgataAncillaryFatima(path,name);
        theAncillary  [ii] = (AgataAncillaryScheme*)    theFatima;
        theConstructed[ii] = (AgataDetectorConstructed*)theFatima;
        break;
      case 19:  // PARIS
        theParis          = new AgataAncillaryParis(path,name);
        theAncillary  [ii] = (AgataAncillaryScheme*)    theParis;
        theConstructed[ii] = (AgataDetectorConstructed*)theParis;
        break;

      case 20:  // GDSI chamber central Ring
        theGSIChambRing          = new AgataAncillaryGSIChambRing(path,name);
        theAncillary  [ii] = (AgataAncillaryScheme*)    theGSIChambRing;
        theConstructed[ii] = (AgataDetectorConstructed*)theGSIChambRing;
        break;
      case 21: // SPIDER FROM LNL 7 trapezoidal Si with support
	theSpider           = new AgataAncillarySpider(path,name);
	theAncillary[ii]    = (AgataAncillaryScheme*)    theSpider;
	theConstructed[ii]  = (AgataDetectorConstructed*)theSpider;
	break;
      case 22:  // Lycca
	theLycca           = new AgataAncillaryLycca(path,name);
	theAncillary  [ii] = (AgataAncillaryScheme*)    theLycca;
	theConstructed[ii] = (AgataDetectorConstructed*)theLycca;
	break;
	
      case 66: // GJ neutron devices
	theNDet            = new AgataAncillaryNDet(path,name);
	theAncillary  [ii] = (AgataAncillaryScheme*)    theNDet;
	theConstructed[ii] = (AgataDetectorConstructed*)theNDet;
 	break;
      case 23://NordBall NDet
	theNordBallNDet    = new AgataAncillaryNordBallNDet(path,name);
	theAncillary  [ii] = (AgataAncillaryScheme*)    theNordBallNDet;
	theConstructed[ii] = (AgataDetectorConstructed*)theNordBallNDet;
 	break;
      case 24:  // Orsay Plastic
	theOrsayPlastic            = new OrsayPlastic(path,name);
	theAncillary  [ii] = (AgataAncillaryScheme*)    theOrsayPlastic;
	theConstructed[ii] = (AgataDetectorConstructed*)theOrsayPlastic;
	break;
#ifdef MINIBALL
      case 25: //Miniball
	theMiniball = new Miniball();
	theAncillary  [ii] = (AgataAncillaryScheme*)    theMiniball;
	theConstructed[ii] = (AgataDetectorConstructed*)theMiniball;
	break;
#endif

      case 26:  // HoneyComb
        theHC          = new AgataAncillaryHC(path,name);
        theAncillary  [ii] = (AgataAncillaryScheme*)    theHC;
        theConstructed[ii] = (AgataDetectorConstructed*)theHC;
 	break;
 	
      case 27:  // HoneyComb
        theGanilChamb          = new AgataAncillaryGanilChamb(path,name);
        theAncillary  [ii] = (AgataAncillaryScheme*)    theGanilChamb;
        theConstructed[ii] = (AgataDetectorConstructed*)theGanilChamb;
 	break;

    case 28: //Oups
      theOups = new AgataAncillaryOups(path,name);
      theAncillary[ii]=(AgataAncillaryScheme*)    theOups;
      theConstructed[ii]=(AgataDetectorConstructed*)theOups;
      break;
    case 29:  // Galileo Plunger
      theGalileoPlunger            = new GalileoPlunger(path,name);
      theAncillary[ii]=(AgataAncillaryScheme*)    theGalileoPlunger;
      theConstructed[ii]=(AgataDetectorConstructed*)theGalileoPlunger;
      break;
	
/*    case 30:  // Sigma
        theSigma          = new AgataAncillarySigma(path,name);
        theAncillary  [ii] = (AgataAncillaryScheme*)    theSigma;
        theConstructed[ii] = (AgataDetectorConstructed*)theSigma;
 	break;
*/	
     case 31:  // Diamant plunger
        theDiamPlung          = new AgataAncillaryDiamant_FP(path,name);
        theAncillary  [ii] = (AgataAncillaryScheme*)    theDiamPlung;
        theConstructed[ii] = (AgataDetectorConstructed*)theDiamPlung;
 	break;
     case 32:  // Diamant Tgt
        theDiamFTgt          = new AgataAncillaryDiamant_FTgt(path,name);
        theAncillary  [ii] = (AgataAncillaryScheme*)    theDiamFTgt;
        theConstructed[ii] = (AgataDetectorConstructed*)theDiamFTgt;
 	break;
      case 35:  // LNL Chamber
      theLNLChamb            = new AgataAncillaryLNLChamb(path,name);
      theAncillary  [ii] = (AgataAncillaryScheme*)    theLNLChamb;
      theConstructed[ii] = (AgataDetectorConstructed*)theLNLChamb;
      break;
      case 36:  // LNL GRIT
      theLNLGRIT            = new AgataAncillaryLNLGRIT(path,name);
      theAncillary  [ii] = (AgataAncillaryScheme*)    theLNLGRIT;
      theConstructed[ii] = (AgataDetectorConstructed*)theLNLGRIT;
     break;

     
#endif
      default:
	numAnc--;
	break;

      // default:
      // 	theShell       = new AgataAncillaryShell(path,name);
      // 	theAncillary  [ii] = (AgataAncillaryScheme*)    theShell;
      // 	theConstructed[ii] = (AgataDetectorConstructed*)theShell;
      // 	break;
      }
    if( aType.find(" ", position) != string::npos ) {
      position = aType.find(" ", position);
      aType = aType.substr(position, length);
    }
  }



   //Here we should check for addons...
  std::vector<void*>::iterator itAddOns = AddOns.begin();
  void*(*Constructor)(G4String,G4String);
  for(; itAddOns!=AddOns.end(); ++itAddOns){
    Constructor=(void*(*)(G4String,G4String))dlsym(*itAddOns,"Constructor");
    char *errormsg = dlerror();
    if(errormsg) {
      printf("dlsym %s" , errormsg);
      exit(0);
    }
    if(Constructor){
      AgataAncillaryScheme *anc = static_cast<AgataAncillaryScheme*>
	(Constructor(path,name));
      numAnc++;
      if(numAnc==whichAnc.size()){
	whichAnc[numAnc-1]=1000000+numAnc;
	theAncillary[numAnc-1]=(AgataAncillaryScheme*)anc;
	theConstructed[numAnc-1]=(AgataDetectorConstructed*)anc;
      } else {
	whichAnc.push_back(1000000+numAnc);
	theAncillary.push_back((AgataAncillaryScheme*)anc);
	theConstructed.push_back((AgataDetectorConstructed*)anc);
      }
    }
  }
}
#endif
#endif
#endif
#endif

AgataDetectorAncillary::~AgataDetectorAncillary()
{}

////////////////////////////////////////////////////////////
///// The Placement() method calls (in the proper sequence)
///// the methods of the ancillary detector class which has
///// been instantiated in the constructor
/////////////////////////////////////////////////////////////
void AgataDetectorAncillary::Placement()
{  
  for( G4int ii=0; ii<numAnc; ii++ ) {
    if( theAncillary[ii]->FindMaterials() ) return;
    theAncillary  [ii]->GetDetectorConstruction();
    theAncillary  [ii]->InitSensitiveDetector();
    theConstructed[ii]->Placement();
  }
  this->FillAncLut();
  ///////////////////////////////////////////////////////////////
  /// Copy the offset LUT (not strictly needed for AGATA, but
  /// useful for other applications
  //////////////////////////////////////////////////////////////
  G4RunManager* runManager = G4RunManager::GetRunManager();
  AgataDetectorConstruction* theDetector  = (AgataDetectorConstruction*) runManager->GetUserDetectorConstruction();
  theDetector->CopyOffset( ancLut );
}

///////////////////////////////////////////////////////////
/// ancLut tells which of the ancillaries uses a specific
/// offset for AgataSensitiveDetector
///////////////////////////////////////////////////////////
#ifdef FIXED_OFFSET
void AgataDetectorAncillary::FillAncLut()
{
  G4int maxIndex = -1;
  G4int ii,/* jj,*/ offs;
  
  for( ii=0; ii<numAnc; ii++ ) {
    if( maxIndex < ( theAncillary[ii]->GetAncOffset() + ( theAncillary[ii]->GetNumAncSd() - 1 ) * 1000 ) ) {
      maxIndex = theAncillary[ii]->GetAncOffset() + ( theAncillary[ii]->GetNumAncSd() - 1 ) * 1000;
    }
  }
  maxIndex /= 1000;
  
  ancLut.clear();
  ancLut.resize(maxIndex+1);
  for( ii=0; ii<maxIndex+1; ii++ )
    ancLut[ii] = -1; //> this saves some operations later!!!
  for( ii=0; ii<numAnc; ii++ ) {
    offs = theAncillary[ii]->GetAncOffset();
    for( G4int jj=0; jj<theAncillary[ii]->GetNumAncSd(); jj++ ) {
      ancLut[offs/1000] = ii;
      offs += 1000;
    }
  }
  G4cout << " Filled AncLut! "<< G4endl;
}
#else
void AgataDetectorAncillary::FillAncLut()
{
  ancLut.clear();
  //> this saves some operations later!!! 
  for( G4int jj=0; jj<(minOffset/1000+1); jj++ )
    ancLut.push_back(-1);  
  
  for( G4int ii=0; ii<numAnc; ii++ ) {
    for( G4int jj=0; jj<theAncillary[ii]->GetNumAncSd(); jj++ ) {
      ancLut.push_back( ii );
    }
  }
  for( G4int kk=0;kk<((G4int)ancLut.size()); kk++ )
    G4cout << " ancLut[" << kk << "] = " << ancLut[kk] << G4endl;
}
#endif

G4int AgataDetectorAncillary::GetSegmentNumber( G4int offset, G4int nGe, G4ThreeVector position )
{
  if(offset>=1000000) return 0;
  return theConstructed[ancLut[offset/1000]]->GetSegmentNumber( offset, nGe, position );
}

void AgataDetectorAncillary::ShowStatus()
{
  for( G4int ii=0; ii<numAnc; ii++ ) {
    G4cout << " ---> Ancillary " << theAncillary[ii]->GetAncName() <<
      " has registered " << theAncillary[ii]->GetNumAncSd() << " SensitiveDetector instances"; 
#ifdef FIXED_OFFSET
    G4cout << " starting from offset " << theAncillary[ii]->GetAncOffset();
#endif	      
    G4cout << "." << G4endl;
    theConstructed[ii]->ShowStatus();
  }  
}

void AgataDetectorAncillary::WriteHeader(std::ofstream &outFileLMD, G4double unitLength)
{
  G4int offset = 0, ii, jj;
  
  offset = minOffset;
  for( ii=0; ii<numAnc; ii++ ) {
#ifdef FIXED_OFFSET
    offset = theAncillary[ii]->GetAncOffset() - 1000;
#endif  
    outFileLMD << "ANCIL " << theAncillary[ii]->GetAncName() << " " << theAncillary[ii]->GetNumAncSd();
    for( jj=0; jj<theAncillary[ii]->GetNumAncSd(); jj++ ) {
      offset += 1000;
      outFileLMD << " " << offset;
    }
    outFileLMD << G4endl;
    theConstructed[ii]->WriteHeader(outFileLMD,unitLength);
  }  
}

//////////////////////////////////////////////////////////////
/// This method returns the sum of the number of detectors
/// of each ancillary
//////////////////////////////////////////////////////////////
G4int AgataDetectorAncillary::GetNumberOfDetectors()
{
  G4int totNum = 0;
  for( G4int ii=0; ii<numAnc; ii++ ) {
    totNum += theConstructed[ii]->GetNumberOfDetectors();
  }  
  return totNum;
}

//////////////////////////////////////////////////////////////
/// This method returns the sum of max detector index
/// of each ancillary
//////////////////////////////////////////////////////////////
G4int AgataDetectorAncillary::GetMaxDetectorIndex()
{
  G4int totNum = 0;
  for( G4int ii=0; ii<numAnc; ii++ ) {
    totNum += theConstructed[ii]->GetMaxDetectorIndex();
  }  
  return totNum;
}

//////////////////////////////////////////////////////////////
/// This method returns true if at least one of the
/// ancillaries returns true
//////////////////////////////////////////////////////////////
G4bool AgataDetectorAncillary::GetReadOut()
{
  for( G4int ii=0; ii<numAnc; ii++ ) {
    if(theConstructed[ii]->GetReadOut()) {
      return true;
    }
  }  
  return false;
}

#ifdef GASP
void AgataDetectorAncillary::SetGeometry( G4int geom )
{
  theEuclides->SetGeometry(geom);
}

void AgataDetectorAncillary::ResetNumberOfSi()
{
  theEuclides->ResetNumberOfSi();
}

void AgataDetectorAncillary::ResetMaxSiIndex()
{
  theEuclides->ResetMaxSiIndex();
}

#endif


void AgataDetectorAncillary::AddAdditionalStrucutre(std::string libname)

{
  void *alib = dlopen(libname.c_str(),RTLD_LAZY);
  if(alib){
    void*(*Constructor)(G4String,G4String);
    Constructor=(void*(*)(G4String,G4String))dlsym(alib,"Constructor");
    if(Constructor){
      AddOns.push_back(alib);
    } else {
      std::cout << "Did not find the \"Constructor\" symbol in lib "
		<< libname << ". Skipping\n";
      dlclose(alib);
      exit(-1);
    }
  } else {
    std::cout << "Could not open " << libname << "\n";
    std::cout << "CHECK PATH AND/OR (DY)LD_LIBRARY_PATH\n";
    exit(-1);
  }
}
