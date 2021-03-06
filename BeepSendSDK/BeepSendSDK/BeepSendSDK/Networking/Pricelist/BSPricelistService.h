//
//  BSPricelistService.h
//  BeepSendSDK
//
//  Created by Vladica Pesic on 6/20/14.
//  Copyright (c) 2014 BeepSend. All rights reserved.
//

#import "BSBaseService.h"

#import "BSPricelist.h"
#import "BSConnection.h"
#import "BSError.h"
#import "BSNetwork.h"

@interface BSPricelistService : BSBaseService

- (void)getCurrentPricelistsForConnection:(BSConnection *)connection withCompletionBlock:(void(^)(BSPricelist *pricelist, NSArray *errors))block;

- (void)getCurrentPricelistsForMeWithCompletionBlock:(void(^)(BSPricelist *pricelist, NSArray *errors))block;

- (void)getPricelistsForConnection:(BSConnection *)connection withCompletionBlock:(void(^)(NSArray *pricelists, NSArray *errors))block;

- (void)getPriceListsForMeWithCompletionBlock:(void(^)(NSArray *pricelists, NSArray *errors))block;

- (void)getPricelistAsCSVForConnection:(BSConnection *)connection onCompletion:(void(^)(NSString *pricelist, NSArray *errors))block;

- (void)getPricelistDiffForConnection:(BSConnection *)connection withPricelist1:(BSPricelist *)pricelist1 andPricelist2:(BSPricelist *)pricelist2 onCompletion:(void(^)(BSNetwork *diff, NSArray *error))block;

- (void)getPricelistDiffAsCSVForConnection:(BSConnection *)connection withPricelist1:(BSPricelist *)pricelist1 andPricelist2:(BSPricelist *)pricelist2 onCompletion:(void(^)(NSString *diff, NSArray *error))block;

@end
