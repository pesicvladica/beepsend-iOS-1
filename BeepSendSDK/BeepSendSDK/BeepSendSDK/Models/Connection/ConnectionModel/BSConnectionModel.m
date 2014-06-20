//
//  BSConnectionModel.m
//  BeepSendSDK
//
//  Created by Vladica Pesic on 6/19/14.
//  Copyright (c) 2014 BeepSend. All rights reserved.
//

#import "BSConnectionModel.h"

@interface BSConnectionModel ()

@property (nonatomic, strong, readwrite) NSString *cAPIToken;

@property (nonatomic, strong, readwrite) BSCallbacksModel *callbacks;

@property (nonatomic, strong, readwrite) NSString *customer;
@property (nonatomic, strong, readwrite) NSString *description;
@property (nonatomic, strong, readwrite) NSString *label;
@property (nonatomic, strong, readwrite) NSString *systemID;
@property (nonatomic, strong, readwrite) NSNumber *cTLVForMCCAndMNC;//Tag-Length-Value field for returning mcc and mnc in DLR.
@property (nonatomic, strong, readwrite) NSNumber *type;//Type of connection, 1 for SMS connection or 2 for HLR connection.

@property (nonatomic, strong, readwrite) NSArray *users;

@property (nonatomic, strong, readwrite) BSWalletModel *wallet;

@property (nonatomic, strong, readwrite) NSString *whitelist;

@end

@implementation BSConnectionModel

#pragma mark - Initialization

- (instancetype)initWithID:(NSString *)objectID andTitle:(NSString *)title
{
	if (self = [super initWithID:@"-1" andTitle:@"Irregular connection"]) {
		
	}
	return self;
}

- (BSConnectionModel *)initConnectionWithID:(NSString *)cID
								   apiToken:(NSString *)cAPIToken
								  callbacks:(BSCallbacksModel *)cCallbacks
								   customer:(NSString *)cCustomer
								description:(NSString *)cDescription
									  label:(NSString *)cLabel
								   systemID:(NSString *)cSystemID
							tlvformccandmnc:(NSNumber *)cTlvformccandmnc
									   type:(NSNumber *)cType
									  users:(NSArray *)cUsers
									 wallet:(BSWalletModel *)cWallet
								  whitelist:(NSString *)cWhitelist
{
	if (self = [super initWithID:cID andTitle:cLabel]) {
		_apiToken = cAPIToken;
		_callbacks = cCallbacks;
		_customer = cCustomer;
		_description = cDescription;
		_label = cLabel;
		_systemID = cSystemID;
		_TLVForMCCAndMNC = cTlvformccandmnc;
		_type = cType;
		_users = cUsers;
		_wallet = cWallet;
		_whitelist = cWhitelist;
	}
	return self;
}

@end
