//
//  BSDLRReportModel.m
//  BeepSendSDK
//
//  Created by Vladica Pesic on 6/25/14.
//  Copyright (c) 2014 BeepSend. All rights reserved.
//

#import "BSDLRReportModel.h"

@interface BSDLRReportModel ()

@property (nonatomic, strong, readwrite) NSString *responseStatus;
@property (nonatomic, strong, readwrite) NSNumber *responseCode;

@end

@implementation BSDLRReportModel

#pragma mark - Initialization

- (instancetype)initWithID:(NSString *)objectID andTitle:(NSString *)title
{
	if (self = [super initWithID:@"-1" andTitle:@"Irregular DLR Report"]) {
		
	}
	return self;
}

- (BSDLRReportModel *)initReportWithResponseStatus:(NSString *)rStatus
								   andResponseCode:(NSNumber *)rCode
{
	if (self = [super initWithID:@"0" andTitle:@"Timestamp"]) {
		_responseStatus = rStatus;
		_responseCode = rCode;
	}
	return self;
}

@end
