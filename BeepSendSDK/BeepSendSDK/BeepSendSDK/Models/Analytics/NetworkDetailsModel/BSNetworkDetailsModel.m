//
//  BSNetworkDetailsModel.m
//  BeepSendSDK
//
//  Created by Vladica Pesic on 7/3/14.
//  Copyright (c) 2014 BeepSend. All rights reserved.
//

#import "BSNetworkDetailsModel.h"

@interface BSNetworkDetailsModel ()

@property (nonatomic, strong, readwrite) BSMCCMNCModel *mccmnc;
@property (nonatomic, strong, readwrite) BSStatisticsModel *statistics;
@property (nonatomic, strong, readwrite) NSNumber *total;

@end


@implementation BSNetworkDetailsModel

#pragma mark - Initialization

- (instancetype)initWithID:(NSString *)objectID andTitle:(NSString *)title
{
	if (self = [super initWithID:@"-1" andTitle:@"Irregular Network details"]) {
		
	}
	return self;
}

- (BSNetworkDetailsModel *)initWithMCCMNC:(BSMCCMNCModel *)nMccmnc statistics:(BSStatisticsModel *)nStatistics total:(NSNumber *)nTotal
{
	if (self = [super initWithID:@"0" andTitle:@"Network details"]) {
		_mccmnc = nMccmnc;
		_statistics = nStatistics;
		_total = nTotal;
	}
	return self;
}

@end
