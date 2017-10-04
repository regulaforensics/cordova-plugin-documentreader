//
//  RGLDocumentReader.h
//  CordovaDocumentReader
//
//  Created by Dmitry Smolyakov on 9/16/17.
//  Copyright © 2017 Dmitry Smolyakov. All rights reserved.
//

#import <Cordova/CDVPlugin.h>
#import <Foundation/Foundation.h>

@class DocReader;

@interface RGLDocumentReader : CDVPlugin

@property (nonatomic, strong) DocReader *docReader;

- (void) initReader:(CDVInvokedUrlCommand*)command;
- (void) scanDocument:(CDVInvokedUrlCommand*)command;

@end
