//
//  BSAPWallet.m
//  BeepSendSDK
//
//  Created by Vladica Pesic on 7/4/14.
//  Copyright (c) 2014 BeepSend. All rights reserved.
//

#import "BSAPWallet.h"

#import "BSAPConnection.h"
#import "BSAPCUser.h"

#import "BSWallet.h"

@implementation BSAPWallet

#pragma mark - Inherited methods

+ (id)classFromDict:(NSDictionary *)dictionary
{
	if (![dictionary isKindOfClass:[NSDictionary class]]) {
		return nil;
	}
	
	BSAPWallet *wallet = [super classFromDict:dictionary];

	wallet.connections = [BSAPConnection arrayOfObjectsFromArrayOfDictionaries:wallet.connections];
	wallet.users = [BSAPCUser arrayOfObjectsFromArrayOfDictionaries:wallet.users];
	
	return wallet;
}

- (id)convertToModel
{
	return [[BSWallet alloc] initWalletWithID:_id
											 named:_name
										   balance:_balance
									minimumBalance:_notify_limit
									   connections:[BSAPConnection arrayOfModelsFromArrayOfObjects:_connections]
											 users:[BSAPCUser arrayOfModelsFromArrayOfObjects:_users]];
}

#pragma mark - Public methods

+ (NSArray *)arrayOfObjectsFromArrayOfDictionaries:(NSArray *)array
{
	NSMutableArray *results = [@[] mutableCopy];
	for (id object in array) {
		[results addObject:[BSAPWallet classFromDict:object]];
	}
	return [NSArray arrayWithArray:results];
}

+ (BSAPWallet *)convertFromWalletModel:(BSWallet *)walletModel
{

	BSAPWallet *wallet = [[BSAPWallet alloc] init];
	
	if ([walletModel.objectID isEqualToString:@"-1"]) {
		return wallet;
	}
	
	wallet.id = [walletModel.objectID isEqualToString:@"0"] ? nil : walletModel.objectID;
	
	wallet.name = walletModel.name;
	wallet.balance = walletModel.balance;
	wallet.notify_limit = walletModel.minimumBalanceForNotification;
	
	//TODO: Add conversion for arrays
	
	return wallet;
}

@end
