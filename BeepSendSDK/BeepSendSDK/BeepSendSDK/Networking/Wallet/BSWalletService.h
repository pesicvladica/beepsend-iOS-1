//
//  BSWalletService.h
//  BeepSendSDK
//
//  Created by Vladica Pesic on 7/4/14.
//  Copyright (c) 2014 BeepSend. All rights reserved.
//

#import "BSBaseService.h"

#import "BSWallet.h"
#import "BSEmailModel.h"
#import "BSTransferModel.h"
#import "BSLogModel.h"

@interface BSWalletService : BSBaseService

- (void)getAllWalletsWithCompletionBlock:(void(^)(NSArray *wallets, id error))block;

- (void)getWalletDetailsForID:(NSString *)walletID withCompletionBlock:(void(^)(BSWallet *wallet, id error))block;

- (void)updateWallet:(BSWallet *)wallet withName:(NSString *)wName notifyLimit:(NSNumber *)wLimit withCompletionBlock:(void(^)(BSWallet *wallet, id error))block;

- (void)getEmailsForWallet:(BSWallet *)wallet withCompletionBlock:(void(^)(NSArray *emails, id error))block;
- (void)getEmailForWallet:(BSWallet *)wallet andEmailID:(NSString *)emailID withCompletionBlock:(void(^)(BSEmailModel *email, id error))block;
- (void)addEmail:(NSString *)email toWallet:(BSWallet *)wallet withCompletionBlock:(void(^)(BSEmailModel *email, id error))block;
- (void)deleteEmailInWallet:(BSWallet *)wallet email:(BSEmailModel *)email withCompletionBlock:(void(^)(BOOL success, id error))block;

- (void)getTransactionLogForWallet:(BSWallet *)wallet withCompletionBlock:(void(^)(NSArray *log, id error))block;
- (void)transferFunds:(NSNumber *)ammount fromWallet:(BSWallet *)wallet1 toWallet:(BSWallet *)wallet2 withCompletionBlock:(void(^)(BSTransferModel *transfer, id error))block;

@end
