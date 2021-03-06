//
//  BSPricelistModel.m
//  BeepSendSDK
//
//  Created by Vladica Pesic on 6/23/14.
//  Copyright (c) 2014 BeepSend. All rights reserved.
//

#import "BSPricelist.h"

@interface BSPricelist ()

@property (nonatomic, strong, readwrite) NSString *pricelistID;
@property (nonatomic, strong, readwrite) NSArray *networks;
@property (nonatomic, strong, readwrite) NSNumber *networkCount;
@property (nonatomic, strong, readwrite) NSDate *saved;
@property (nonatomic, assign, readwrite) NSNumber *active;
@property (nonatomic, strong, readwrite) NSDate *firstViewed;

@end

@implementation BSPricelist

#pragma mark - Properties

- (NSString *)pricelistID
{
	return [BSHelper isNilOrEmpty:_pricelistID] ? @"0" : [_pricelistID isKindOfClass:[NSNumber class]] ? [(NSNumber *)_pricelistID stringValue] : _pricelistID;
}

- (NSArray *)networks
{
	return _networks ? _networks : @[];
}

- (NSNumber *)networkCount
{
	return _networkCount ? _networkCount : @0;
}

- (NSNumber *)active
{
	return _active ? _active : @0;
}

#pragma mark - Initialization

- (instancetype)initWithID:(NSString *)objectID andTitle:(NSString *)title
{
	if (self = [super initWithID:@"-1" andTitle:@"Irregular pricelist"]) {
		_pricelistID = @"-1";
	}
	return self;
}

- (BSPricelist *)initPricelistWithID:(NSString *)pID
							networks:(NSArray *)pNetworks
						networkCount:(NSNumber *)nCount
						  timeOfSave:(NSDate *)nSaved
							  active:(NSNumber *)active
					 timeOfFirstView:(NSDate *)nFirstView
{
	if (self = [super initWithID:pID andTitle:@"Pricelist"]) {
		_pricelistID = pID;
		_networks = pNetworks;
		_networkCount = nCount;
		_saved = nSaved;
		_active = active;
		_firstViewed = nFirstView;
	}
	return self;
}

@end
