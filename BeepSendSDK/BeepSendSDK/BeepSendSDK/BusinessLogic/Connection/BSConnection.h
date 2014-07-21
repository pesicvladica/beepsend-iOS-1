//
//  BSConnection.h
//  BeepSendSDK
//
//  Created by Vladica Pesic on 7/8/14.
//  Copyright (c) 2014 BeepSend. All rights reserved.
//

#import "BSGeneralModel.h"
#import "BSStructs.h"

@class BSPricelist;
@class BSCallbacks;
@class BSBatch;
@class BSEstimateCost;
@class BSHLR;
@class BSLookup;

@class BSMessage;
@class BSWallet;

@interface BSConnection : BSGeneralModel

//Connection ID
@property (nonatomic, strong, readonly) NSString *connectionID;
//Connection type: HLR connection or SMS connection
@property (nonatomic, assign, readonly) BSConnectionType type;

//Users who have privileges to read/write connection
@property (nonatomic, strong, readonly) NSArray *users;
//Wallet that belongs to connection
@property (nonatomic, strong, readonly) BSWallet *wallet;

//Properties that can be edited by user
@property (nonatomic, strong) NSString *label;
@property (nonatomic, strong) NSString *description;
@property (nonatomic, strong) NSString *systemID;//Login name

//Specifies if connection is default
@property (nonatomic, assign) BOOL defaultConnection;

//Connection API token
@property (nonatomic, strong, readonly) NSString *apiToken;

//Callbacks URLs
@property (nonatomic, strong) BSCallbacks *callbackURLs;

//Customer that ownes connection
@property (nonatomic, strong, readonly) NSString *customer;

//Tag-Length-Value field for returning mcc and mnc in DLR.
@property (nonatomic, strong, readonly) NSNumber *TLVForMCCAndMNC;

//Whitelist
@property (nonatomic, strong, readonly) NSArray *whitelist;

//Connection password
@property (nonatomic, strong, readonly) NSString *password;

- (BSConnection *)initConnectionWithID:(NSString *)cID;

- (BSConnection *)initConnectionWithID:(NSString *)cID
							  apiToken:(NSString *)cAPIToken
							 callbacks:(BSCallbacks *)cCallbacks
							  customer:(NSString *)cCustomer
						   description:(NSString *)cDescription
								 label:(NSString *)cLabel
							  systemID:(NSString *)cSystemID
					   tlvformccandmnc:(NSNumber *)cTlvformccandmnc
								  type:(BSConnectionType)cType
								 users:(NSArray *)cUsers
								wallet:(BSWallet *)cWallet
							 whitelist:(NSArray *)cWhitelist
							  password:(NSString *)password;

//Copy constructor with new API token
- (BSConnection *)initWithConnectionModel:(BSConnection *)connectionModel
							 withNewToken:(NSString *)newToken;

//Copy constructor with new password
- (BSConnection *)initWithConnectionModel:(BSConnection *)connectionModel
						  withNewPassword:(NSString *)newPassword;

- (BSConnection *)initConnectionWithID:(NSString *)cID
								 label:(NSString *)cLabel
							  systemID:(NSString *)cSystemID
								  type:(BSConnectionType)cType;

//Initiate connection with API token
+ (BSConnection *)currentConnection;

//After made changes it is necessary to call method updateConnection
- (void)updateConnection;

//If API token is compromised use this method for token reset
- (void)resetConnectionToken;

//Returns pricelists
- (void)getPricelistsOnCompletion:(void(^)(NSArray *pricelists))block;

//Returns current pricelists
- (void)getCurrentPricelistOnCompletion:(void(^)(BSPricelist *pricelist))block;

//Send message
//Returns number of messages
- (NSInteger)sendSMS:(BSMessage *)message withCompletionBlock:(void(^)(BSMessage *message, id error))block;

//Send messages
//Returns number of messages
- (NSInteger)sendMultipleSMS:(NSArray *)messages withCompletionBlock:(void(^)(NSArray *messages, id error))block;

- (NSInteger)smsCountForMessage:(BSMessage *)message;
- (NSInteger)smsCountForMessages:(NSArray *)messages;

//Validate SMS
- (void)validateSMS:(BSMessage *)message onCompletion:(void(^)(BSMessage *message, id error))block;

//Get sms details
- (void)getDetailsForSMS:(BSMessage *)message onCompletion:(void(^)(BSLookup *lookup, id error))block;

//Get sms details based on filters
- (void)getDetailsForMessagesSentTo:(NSString *)recipient sentFrom:(NSString *)sender usedBatch:(BSBatch *)batch beforeDate:(NSDate *)bDate afterDate:(NSDate *)aDate forNextPage:(BOOL)nextPage onCompletion:(void(^)(NSArray *lookups, id error))block;

//How many SMS objects to fetch. Maximum 200, default 100.
- (void)setLookupPageLimit:(NSNumber *)lookupPageLimit;

//Get batch details
- (void)getDetailsForBatch:(BSBatch *)batch onCompletion:(void(^)(BSBatch *batch, id error))block;

//Get previous batches
- (void)getPreviousBatchesOnCompletion:(void(^)(NSArray *batches, id error))block;

//Estimates message cost (not necessarily accurate)
- (void)estimateSMSCostForMessages:(NSArray *)messages onCompletion:(void(^)(NSArray *cost, id error))block;

//Do immediate HLR for given number
- (void)immediateHLRForNumber:(NSString *)phoneNumber onCompletion:(void(^)(BSHLR *hlr, id error))block;

//Validate HLR for phone number
- (void)validateHLRForNumber:(NSString *)phoneNumber onCompletion:(void(^)(BSHLR *hlr, id error))black;



@end
