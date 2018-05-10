//
//  RGLDocumentReader.m
//  CordovaDocumentReader
//
//  Created by Dmitry Smolyakov on 9/16/17.
//  Copyright © 2017 Dmitry Smolyakov. All rights reserved.
//

#import "RGLDocumentReader.h"
@import DocumentReader;

@implementation RGLDocumentReader

- (void) initReader:(CDVInvokedUrlCommand*)command {

    NSData *licenseData = [[command arguments] objectAtIndex:0];

    DocReader *docReader = [[DocReader alloc] initWithProcessParams:nil];
    docReader.processParams.scenario = @"MrzOrBarcode";
    docReader.videoCaptureMotionControl = NO;

    NSError *error = nil;
    BOOL docReaderIsReady = [docReader initializeReaderWithLicense:licenseData error:&error];

    self.docReader = docReader;

    CDVPluginResult* pluginResult;
    if (docReaderIsReady) {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:nil];
    }
    else {
        pluginResult = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsString:error.localizedDescription];
    }
    [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
}

- (void) scanDocument:(CDVInvokedUrlCommand*)command {

                [self.docReader showScanner:self.viewController completion:^(DocReaderAction action, DocumentReaderResults *result, NSString *error) {
                    switch (action) {
                        case DocReaderActionComplete: {
                            if (result != nil) {
                                NSMutableDictionary *totalResults = [NSMutableDictionary new];
                                NSMutableArray *jsonResults = [NSMutableArray array];
                                for (DocumentReaderJsonResultGroup *resultObject in result.jsonResult.results) {
                                    [jsonResults addObject:resultObject.jsonResult];
                                }
                                [totalResults setObject:jsonResults forKey:@"jsonResult"];
                                UIImage *image = [result getGraphicFieldImageByTypeWithFieldType:GraphicFieldTypeGf_DocumentFront source:ResultTypeRawImage];
                                NSString *base64Image = [self encodeToBase64String:image];
                                if (image != nil) {
                                    [totalResults setObject:base64Image forKey:@"image"];
                                }
                                CDVPluginResult* pluginResult = [CDVPluginResult
                                                                 resultWithStatus:CDVCommandStatus_OK
                                                                 messageAsDictionary:[totalResults copy]];
                                [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
                            }
                        }
                        break;
                        case DocReaderActionCancel: {
                            CDVPluginResult* pluginResult = [CDVPluginResult
                                                             resultWithStatus:CDVCommandStatus_OK
                                                             messageAsString:@"Cancelled by user"];
                            [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
                        }
                        break;
                        case DocReaderActionError: {
                            CDVPluginResult* pluginResult = [CDVPluginResult
                                                             resultWithStatus:CDVCommandStatus_ERROR
                                                             messageAsString:error];
                            [self.commandDelegate sendPluginResult:pluginResult callbackId:command.callbackId];
                        }
                        break;
                        default:
                        break;
                    }
                }];
}

- (NSString *) encodeToBase64String:(UIImage *)image {
    return [UIImageJPEGRepresentation(image, 0.8) base64EncodedStringWithOptions:NSDataBase64Encoding64CharacterLineLength];
}

@end
