//
//  DocumentReader.h
//  DocumentReader
//
//  Created by Игорь Клещёв on 15.04.17.
//  Copyright © 2017 Regula Forensics. All rights reserved.
//

#import <UIKit/UIKit.h>

//! Project version number for DocumentReader.
FOUNDATION_EXPORT double DocumentReaderVersionNumber;

//! Project version string for DocumentReader.
FOUNDATION_EXPORT const unsigned char DocumentReaderVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <DocumentReader/PublicHeader.h>

typedef NS_ENUM(NSInteger, DocumentReaderErrorCode)
{
    RPRM_Error_NoError_ = 0,
    RPRM_Error_LicenseError_ = 1,
    RPRM_Error_NotInitialized_ = 2,
    RPRM_Error_BadInputParameters_ = 3,
    
};
typedef NS_ENUM(NSInteger, DocumentReaderCommand)
{
    ePC_ProcMgr_SetLicense_ = 12100,                          // initialize ProcMgr
    ePC_ProcMgr_Process_ = 12101,                             // process images and return result
    ePC_ProcMgr_ProcessAsync_ = 12102,                        // start asynchronous processing and return currently available
    ePC_ProcMgr_ProcessImage_ = 12104,                        // process image/images and return result
    ePC_ProcMgr_StartNewDocument_ = 12105,
    ePC_ProcMgr_StartNewPage_ = 12106,
    ePC_ProcMgr_Unload_ = 12107,                              // unload ProcMgr
};

typedef NS_ENUM(NSInteger, DocumentReaderLight)
{
    DocumentReaderLight_OFF               = 0x00000000, // Light Off
    DocumentReaderLight_OVI               = 0x00000001, // Light for OVI
    DocumentReaderLight_White_Top         = 0x00000002, // Light White Top
    DocumentReaderLight_White_Side        = 0x00000004, // Light White Side
    DocumentReaderLight_White_Front       = 0x00800000, // Light White (single light source)
    DocumentReaderLight_IR_Top            = 0x00000008, // Light IR Top
    DocumentReaderLight_IR_Side           = 0x00000010, // Light IR Side
    DocumentReaderLight_IR_Front          = 0x01000000, // Light IR (single light source)
    DocumentReaderLight_IR_870            = 0x01000000, // Light IR 870 (mod. 8803)
    DocumentReaderLight_White_Gray        = 0x02000000, // Light GRAY (grayscale made from WHITE)
    DocumentReaderLight_OVD               = 0x04000000, // Light OVD (hologram visualization)
    
    DocumentReaderLight_UV                = 0x00000080, // Light UV
    DocumentReaderLight_IR_Luminescence   = 0x00000100, // Light Green Front
    DocumentReaderLight_AXIAL_White_Front = 0x00000200, // Light Axial (3M) White
    DocumentReaderLight_AXIAL_White_Left  = 0x00000400, // Light Axial (3M) White Left
    DocumentReaderLight_AXIAL_White_Right = 0x00000800, // Light Axial (3M) White Right
    
    DocumentReaderLight_IR_700            = 0x00001000, // Light IR 700 (mod. 8803)
    DocumentReaderLight_IR_720            = 0x00001000, // Light IR 720 (mod. 8850)
    DocumentReaderLight_IR_940            = 0x00002000, // Light IR 940 (mod. 8803, 8850)
    
    DocumentReaderLight_White_Full        = (DocumentReaderLight_White_Top | DocumentReaderLight_White_Side),
    DocumentReaderLight_IR_Full           = (DocumentReaderLight_IR_Top    | DocumentReaderLight_IR_Side),
    DocumentReaderLight_AXIAL_White_Full  = (DocumentReaderLight_AXIAL_White_Left | DocumentReaderLight_AXIAL_White_Right),
    
    DocumentReaderLight_Transmitted       = 0x00000020, // transmitted light
    DocumentReaderLight_Transmitted_IR    = 0x00000040, // transmitted IR light
    DocumentReaderLight_AntiStokes        = 0x00010000, // Anti Stokes light
    };

@interface ImageResult: NSObject

@property (nonatomic, strong) UIImage *image;
@property (nonatomic, assign) NSInteger pageIndex;
@property (nonatomic, assign) DocumentReaderLight light;

@end

@interface DocumentReader: NSObject

+(DocumentReaderErrorCode)process:
(DocumentReaderCommand) p_cmd
                       inputImage:(UIImage *)p_inputImage
                        inputJSON:(NSString *)p_inputJSON
                      outputImages:(NSArray **)p_outputImages
                       outputJSON:(NSString **)p_outputJSON;

+(DocumentReaderErrorCode)process:
(DocumentReaderCommand) p_cmd
                        inputData:(NSData *)p_inputData
                        inputJSON:(NSString *)p_inputJSON
                       outputJSON:(NSString **)p_outputJSON;

@end
