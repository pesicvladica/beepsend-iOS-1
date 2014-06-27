//
//  BSAPDLRReport.m
//  BeepSendSDK
//
//  Created by Vladica Pesic on 6/25/14.
//  Copyright (c) 2014 BeepSend. All rights reserved.
//

#import "BSAPDLRReport.h"

#import "BSDLRReportModel.h"

@implementation BSAPDLRReport

#pragma mark - Inherited methods

- (id)convertToModel
{
	return [[BSDLRReportModel alloc] initReportWithResponseStatus:_status?_status:@"" andResponseCode:_error?_error:@0];
}

@end
