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
};

@interface DocumentReader: NSObject

+(DocumentReaderErrorCode)process:
(DocumentReaderCommand) p_cmd
                       inputImage:(UIImage *)p_inputImage
                        inputJSON:(NSString *)p_inputJSON
                      outputImage:(UIImage **)p_outputImage
                       outputJSON:(NSString **)p_outputJSON;

+(DocumentReaderErrorCode)process:
(DocumentReaderCommand) p_cmd
                        inputData:(NSData *)p_inputData
                        inputJSON:(NSString *)p_inputJSON
                       outputJSON:(NSString **)p_outputJSON;

@end
