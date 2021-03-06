//
//  BSAPIConfiguration.h
//  BeepSendSDK
//
//  Created by Vladica Pesic on 6/13/14.
//  Copyright (c) 2014 BeepSend. All rights reserved.
//

/*
 
	BSAPIConfiguration class will contain base url and 
	all methods available on backend
 
 
	Detailed documentation for RESTfull API can be found at:
	http://api.beepsend.com/docs.html
 
 
 */

#import <Foundation/Foundation.h>

@interface BSAPIConfiguration : NSObject

/*
	Host
 */
+ (NSString *)baseURL;

/*
	Add your API token as a parameter in the query string and append 
	to the URL you are trying to reach.
	@"?api_token=abc123"];
 */
+ (NSString *)urlAPIToken;

/*
	User can choose if authorization will be using Query String or HTTP header
	We will use authorization header in this SDK
 
 
	If you prefer keeping the URL untouched, 
	you can use an HTTP header in your request instead.
	In your request, add the Authorization HTTP header
	with your API token as value.
 
	Authorization: Token abc123
 */
+ (NSDictionary *)authorizationHeader;
+ (NSDictionary *)authorizationHeaderForToken:(NSString *)token;

#pragma mark -
#pragma mark - Methods

#pragma mark - Customer

/*
	As a user you belong to a customer. A customer is where your address,
	pay and pricelist information is stored.
 */
+ (NSString *)customer;

#pragma mark - Connections

/*
	To fetch a list of all available connections and 
	their corresponding information.
 */
+ (NSString *)connections;

/*
	For both Connection and User tokens a short-hand tag is available 
	which serves as alias for the connection ID. The label is called "me".
 */
+ (NSString *)connectionsMe;

/*
	Any property of the connection object can be manipulated once authenticated 
	either as that Connection using a Connection token or by authenticating 
	using a User token with read/write access to the Connection.
 */
+ (NSString *)connectionsWithID:(NSString *)connectionID;

/*
	If you think that the connection token used for authenticating with 
	the Beepsend API has been compromised you can use this method 
	(with a user token) to reset the connection token.
 */
+ (NSString *)connectionResetForID:(NSString *)connectionID;

/*
	If you wish to use our legacy HTTP API, you need to supply your connection
	username as well as password for each request. If you don't have your 
	connection password, you can request a new one with this endpoint.
 
	NOTE: A connection token and password are two separate things. 
	A connection password is only used for HTTP API and SMPP.
 */
+ (NSString *)connectionPasswordResetForID:(NSString *)connectionID;

#pragma mark - Recipient Numbers

/*
	As a user you will have associated connections. 
	These connections have access to recipient numbers, 
	which can receive mobile originated messages. 
	The recipient numbers are registered in specific countries,
	which this endpoint will also list.
 */
+ (NSString *)recipientNumbers;

#pragma mark - Pricelist

/*
	The API offers the ability to see every revision made of price lists for 
	each connection. When specifying a revision ID one can fetch the detailed 
	price list at that point in time. If authenticated using a User token, 
	a connection ID needs to be provided too.
 */
+ (NSString *)pricelistCurrentWithID:(NSString *)connectionID;

/*
	For simplicity the tag "me" can be used to select the default assigned 
	connection for the User.
 */
+ (NSString *)pricelistCurrentMe;

/*
	Receive all price lists revisions for a specific connection related to
	the authenticated user.
 */
+ (NSString *)pricelistAllForID:(NSString *)connectionID;

/*
	A connection ID or alias tag "me" must be provided as reference.
 */
+ (NSString *)pricelistAllMe;

/*
	Receive price list (.csv) for given connection.
 */
+ (NSString *)pricelistCSVForID:(NSString *)connectionID;

/*
	Pricelist diff
 */
+ (NSString *)pricelistDiffForConnectionID:(NSString *)connectionID rev1:(NSString *)pricelist1ID rev2:(NSString *)pricelist2ID;

/*
	Pricelist diff as csv
 */
+ (NSString *)pricelistDiffAsCSVForConnectionID:(NSString *)connectionID rev1:(NSString *)pricelist1ID rev2:(NSString *)pricelist2ID;

#pragma mark - Users

/*
	Get details regarding your user.
 */
+ (NSString *)userMe;

/*
	Update email for your user.
 */
+ (NSString *)updateUserEmail;

/*
	Update user password.
 */
+ (NSString *)updateUserPassword;

/*
	If you have forgotten or in other ways lost control over your password, 
	you can issue a reset. When doing so, Beepsend will send an email with 
	a link to where you can get your new password.
 */
+ (NSString *)resetPassword;
+ (NSString *)setNewPasswordWithHash:(NSString *)hash;

/*
	If you think that the user token used for authenticating with the 
	Beepsend API has been compromised you can use this method (with your 
	current user token and password) to reset the user token.
 */
+ (NSString *)resetTokenMe;
+ (NSString *)resetTokenForID:(NSString *)userID;

#pragma mark - Send SMS

/*
	A message can carry 160 characters if in the Latin alphabet and 
	70 if content is Unicode. The Beepsend Gateway will automatically split up 
	the message if the content exceeds the maximum character limit based on 
	the content encoding. When sending UTF-8 or Unicode encoding 
	the Beepsend Gateway will try and convert to GSM7 if possible 
	to avoid splitting at 70 characters.
 */
+ (NSString *)sms;

/*
	Send SMS with specific connection
 */
+ (NSString *)smsForID:(NSString *)connectionID;

#pragma mark - SMS Lookup

/*
	The API can be utilized to get details of any message sent through Beepsend 
	no matter if you submitted it via SMPP or HTTP.

	Get details regarding one message.
 */
+ (NSString *)smsLookupWithID:(NSString *)smsID;

#pragma mark - HLR

/*
	If you have an HLR connection set up with Beepsend this can be used
	to make HLR queries. You still need to identify which connection to use
	as HLR connection for submissions, either by setting the Connection ID or
	by using the "me" alias if your HLR connection is the default connection 
	for the User token.
 */
+ (NSString *)hlrForNumber:(NSString *)number;

+ (NSString *)hlr;

#pragma mark - Validation

/*
	Perform a dry run of SMS sending or HLR lookups.
*/
+ (NSString *)validateSMS;
+ (NSString *)validateHLR;

#pragma mark - Batches

/*
	Get your previous batches with messages.
 */
+ (NSString *)batches;

/*
	Get details for a specific batch.
 */
+ (NSString *)batchesForID:(NSString *)batchID;

/*
	Two way batches
 */
+ (NSString *)twoWayBatchesForID:(NSString *)batchID;

#pragma mark - Analytics

/*
	This call will give you accumulated statistics for all messages sent between
	two specified dates and the accumulated cost for these in Euro (€).
	The call counts all messages submitted via SMPP and HTTP alike.
 
	The call supports a summary for available connections on a User Token, 
	a specific connection or using the short hand alias "me" for the 
	authenticated connection if a Connection token was used when authenticating 
	or the default connection if User token was used instead.
 
	This call does not consider delivery statistics and should merely be used
	for aggregated views on traffic. 
	If no ID is provided the return data set is a list of connections.
 */
+ (NSString *)analyticsSummary;

+ (NSString *)analyticsSummaryMe;

+ (NSString *)analyticsSummaryForID:(NSString *)connectionID;

/*
	This call will give you granular delivery statistics for all messages 
	sorted by each recipient network between two specified dates. 
	The call counts all messages submitted via SMPP and HTTP alike.
 
	The call supports parameter to specify a list of MCC and/or MNC. 
	If these parameters are omitted all MCC and MNC that has traffic 
	will be returned.
 
	The call supports a summary for available connections on used token. 
	Either a specific Connection ID or using the short hand alias "me" for 
	the authenticated connection if Connection token was used when 
	authenticating or the default connection if User token was used instead. 
	If no ID is provided all connections available is returned as list.
 */
+ (NSString *)analyticsNetwork;

+ (NSString *)analyticsNetworkMe;

+ (NSString *)analyticsNetworkForID:(NSString *)connectionID;

/*
	This call will give you delivery statistics for a whole batch.
 */
+ (NSString *)analyticsBatches;

+ (NSString *)analyticsBatchesForID:(NSString *)batchID;

#pragma mark - Conversations

+ (NSString *)conversation;

+ (NSString *)conversationForID:(NSString *)cID;

#pragma mark - Contacts

/*
	Get all contacts belonging to your user. 
	Specify a group ID or name to filter your results.
 
	Update a contact
	Delete a contact
 */
+ (NSString *)contactsForID:(NSString *)contactID;

/*
	Get all contacts
	Add new contacts
 */
+ (NSString *)contacts;

#pragma mark - Contact groups

/*
	Get all contact groups belonging to your user.
	Add new groups
 */
+ (NSString *)contactsGroups;

/*
	Get content of a contact group
	Update groups
	Delete groups
 */
+ (NSString *)contactsGroupsForID:(NSString *)groupID;

#pragma mark - Search contact groups

/*
	Search Contacts
 */
+ (NSString *)searchContacts;

/*
	Search Contact Groups
 */
+ (NSString *)searchContactGroups;

#pragma mark - WalletNotification

/*
	By default, all pricelist and wallet notifications will be sent to the email
	registered to your user. If you wish to have updates sent to more emails 
	you can add external recipients.
 
	Get a list of your external emails.
 */
+ (NSString *)walletsEmailsForID:(NSString *)walletID;

/*
	Get details for a specific wallet
 */
+ (NSString *)walletsEmailsForWalletID:(NSString *)walletID andEmailID:(NSString *)emailID;

#pragma mark - Wallets

/*
	Get info for your wallet
 */
+ (NSString *)wallets;

+ (NSString *)walletsForID:(NSString *)walletID;

/*
	View transactions for given wallet.
 */
+ (NSString *)walletsTransactionForID:(NSString *)walletID;

/*
	Transfer credits between your connection wallets.
 */
+ (NSString *)walletsTransferFundsFromWallet:(NSString *)wallet1 toWallet:(NSString *)wallet2;

#pragma mark - Estimate SMS cost

/*
	Each estimation require a token either assigned to a Connection or a User
	that has a default connection set up. By specifying a label of a different
	Connection belonging to your Company this will instead be used, granted
	the User has access-rights to this Connection. If authenticated by
	User token and no Connection is specified, the default assigned Connection
	will be used.
 */
+ (NSString *)smsCostEstimate;

+ (NSString *)smsCostEstimateForID:(NSString *)connectionID;

#pragma mark - Verify email and phone number

/*
	An email will be sent out after changing your email address asking you
	to verify that you have indeed changed it. Use the unique hash in the 
	verification link to perform the verification.
 */
+ (NSString *)verifyEmailWithHash:(NSString *)hash;

/*
	After changing your phone number. An SMS will be sent out asking you 
	to verify the change. Use the unique hash to verify.
 */
+ (NSString *)verifyPhoneWithHash:(NSString *)hash;

@end
