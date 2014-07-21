//
//  BSAPCAccountManager.m
//  BeepSendSDK
//
//  Created by Vladica Pesic on 6/18/14.
//  Copyright (c) 2014 BeepSend. All rights reserved.
//

#import "BSAPCAccountManager.h"

#import "BSAccountManager.h"

@implementation BSAPCAccountManager

#pragma mark - Inherited methods

- (id)convertToModel
{
	return [[BSAccountManager alloc] initAccountManagerWithName:_name?_name:@"" andEmail:_email?_email:@""];
}

@end
