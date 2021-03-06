//
//  BSMessage.h
//  BeepSendSDK
//
//  Created by Vladica Pesic on 7/8/14.
//  Copyright (c) 2014 BeepSend. All rights reserved.
//

#import "BSGeneralModel.h"

#import "BSBatch.h"

/*!
 @class BSMessage
 @discussion Message object is used when you want to create and send new message
 or when you receive details for some already sent message.
 */
@interface BSMessage : BSGeneralModel

//Required

/*! Sender id. Check below for a list of allowed formats.
 */
@property (nonatomic, strong, readonly) NSString *sender;

/*! Message body.
 */
@property (nonatomic, strong, readonly) NSString *message;

/*! The mobile phone number starting with country code and no + sign. 
	Also referred to sometimes as MSISDN. Supports multiple values in an array.
 */
@property (nonatomic, strong, readonly) NSString *recipient;

// Optional

/*! The id of contants group that have to exist in our system. 
	Supports multiple values in an array.
 */
@property (nonatomic, strong, readonly) NSArray *groups;

/*! Multiple destinations count as multiple messages and will be charged as such.
 */
@property (nonatomic, strong, readonly) NSArray *recipients;

//Additional options

/*! Existing batch of messages
 */
@property (nonatomic, strong) BSBatch *batch;

/*! How long a message is relevant to the end user. 
	If this expires, the message won't continue to be routed.
	Default is infinite.
 */
@property (nonatomic, strong, readonly) NSDate *validTo;

/*! Schedule message to be delivered at a certain time in the future. 
	Note Credits will be deducted from your connection at the time of sending 
	for the price at that time. 
	Therefore we do not encourage delivery dates set long in the future.
 */
@property (nonatomic, strong, readonly) NSDate *sendTime;

/*! normal, flash or binary. If omitted, a normal message will be sent. 
	Flash sms can contain only ASCII alphanumeric characters.
 */
@property (nonatomic, strong, readonly) NSString *messageType;

/*! UTF-8, ISO-8859-15 or Unicode. If omitted, the default charset is UTF-8.
	The unicode uses the UCS2 standard UTF16-BE.
 */
@property (nonatomic, strong, readonly) NSString *usedEncoding;

/*! Specify whether delivery reports should be sent to your DLR Callback URL.
	0: Disable, 1: Always, 2: Only on failure. Default is 1.
 */
@property (nonatomic, assign, readonly) NSInteger shouldReceiveDeliveryReport;

//Available options for binary message

/*! User Data Header. Can be used to send Concatenated or Wap Push messages.
 */
@property (nonatomic, strong, readonly) NSString *userDataHeader;

/*! Data coding settings. 
	For binary messages this is set to 4 (8-bit binary) by default. 
	Should be 0 for gsm7 encoded messages and 8 for UCS-2 encoded messages.
 */
@property (nonatomic, strong, readonly) NSString *dataCodingSettings;

//Message response parameters

/*! Message ID.
 */
@property (nonatomic, strong, readonly) NSString *messageID;

/*! Errors.
 */
@property (nonatomic, strong, readonly) NSArray *errors;

/*! Create Message object
 Copy constructor.
 Used when message is created and sent.
 After we receive response we return same message object with ID or errors.
 
 @param mshID - Message ID
 @param errors - Errors
 @param msg - Message
 
 @return Returns Message object
 */
- (BSMessage *)initMessageWithID:(NSString *)mshID
					   andErrors:(NSArray *)errors
					  forMessage:(BSMessage *)msg;

/*! Create Message object
 Used for initializing message request object with object received from server
 
 @param rMessage - Message body
 @param rReceiver - Receiver
 @param rSender - Sender
 @param rBatchID - Batch ID
 @param rBatchLabel - Batch Label
 @param rSendTime - Send time
 @param rEncoding - Encoding
 @param rType - Type
 @param rValidTo - Valid to
 @param rReceiveDLR - Receive DLR
 @param rGroups - Groups
 @param rUDH - UDH
 @param rDCS - DCS
 
 @return Returns Message object
 */
- (BSMessage *)initWithMessage:(NSString *)rMessage
					  receiver:(id)rReceiver
						sender:(NSString *)rSender
					   batchID:(NSString *)rBatchID
					batchLabel:(NSString *)rBatchLabel
					  sendTime:(NSDate *)rSendTime
				  usedEncoding:(NSString *)rEncoding
				   messageType:(NSString *)rType
					   validTo:(NSDate *)rValidTo
					recieveDLR:(NSNumber *)rReceiveDLR
					 forGroups:(NSArray *)rGroups
				userDataHeader:(NSString *)rUDH
			dataCodingSettings:(NSString *)rDCS;

/*! Create Message object
 Used for initializing message object with object received from server
 
 @param mID - Message ID
 @param mBatch - Batch
 @param mRecipients - Recipients
 @param mSender - Sender
 @param mErrors - Errors
 @param mGroups - Groups
 
 @return Returns Message object
 */
- (BSMessage *)initMessageWithID:(NSString *)mID
						   batch:(BSBatch *)mBatch
					  recipients:(id)mRecipients
						  sender:(NSString *)mSender
						  errors:(NSArray *)mErrors
				 recipientGroups:(NSArray *)mGroups;

/*! Creates normal message for single recipient
 
 @param body - Message body
 @param sender - Message sender (alphanumeric)
 @param recipient - Message recipient (numeric)
 
 @return Returns Message object
 */
+ (BSMessage *)messageWithBody:(NSString *)body
						  from:(NSString *)sender
							to:(NSString *)recipient;

/*! Creates normal message for multiple recipients
 
 @param body - Message body
 @param sender - Message sender (alphanumeric)
 @param recipients - Array of message recipients (array of numbers)
 
 @return Returns Message object
 */
+ (BSMessage *)messageWithBody:(NSString *)body
						  from:(NSString *)sender
					toMultiple:(NSArray *)recipients;

/*! Creates normal message for groups recipients
 
 @param body - Message body
 @param sender - Message sender (alphanumeric)
 @param groups - Array of group recipients (array of groups, array of group IDs)
 
 @return Returns Message object
 */
+ (BSMessage *)messageWithBody:(NSString *)body
						  from:(NSString *)sender
					  toGroups:(NSArray *)groups;

/*! Creates flash message for single recipient
 
 @param body - Message body
 @param sender - Message sender (alphanumeric)
 @param recipient - Message recipient (numeric)
 
 @return Returns Message object
 */
+ (BSMessage *)flashMessageWithBody:(NSString *)body
							   from:(NSString *)sender
								 to:(NSString *)recipient;

/*! Creates flash message for multiple recipients
 
 @param body - Message body
 @param sender - Message sender (alphanumeric)
 @param recipients - Array of message recipients (array of numbers)
 
 @return Returns Message object
 */
+ (BSMessage *)flashMessageWithBody:(NSString *)body
							   from:(NSString *)sender
						 toMultiple:(NSArray *)recipients;

/*! Creates flash message for groups recipients
 
 @param body - Message body
 @param sender - Message sender (alphanumeric)
 @param groups - Array of group recipients (array of groups, array of group IDs)
 
 @return Returns Message object
 */
+ (BSMessage *)flashMessageWithBody:(NSString *)body
							   from:(NSString *)sender
						   toGroups:(NSArray *)groups;

/*! Creates binary message for single recipient
 
 @param body - Message body
 @param sender - Message sender (alphanumeric)
 @param recipient - Message recipient (numeric)
 
 @return Returns Message object
 */
+ (BSMessage *)binaryMessageWithBody:(NSString *)body
								from:(NSString *)sender
								  to:(NSString *)recipient;

/*! Creates binary message for multiple recipients
 
 @param body - Message body
 @param sender - Message sender (alphanumeric)
 @param recipients - Array of message recipients (array of numbers)
 
 @return Returns Message object
 */
+ (BSMessage *)binaryMessageWithBody:(NSString *)body
								from:(NSString *)sender
						  toMultiple:(NSArray *)recipients;

/*! Creates binary message for groups recipients
 
 @param body - Message body
 @param sender - Message sender (alphanumeric)
 @param groups - Array of group recipients (array of groups, array of group IDs)
 
 @return Returns Message object 
 */
+ (BSMessage *)binaryMessageWithBody:(NSString *)body
								from:(NSString *)sender
							toGroups:(NSArray *)groups;

/*! Specify if delivery report should be received
	
 @param receive - 0: Disable, 1: Always, 2: Only on failure. Default is 1.
 */
- (void)receiveDeliveryReportWithOption:(NSInteger)receive;

/*! Specify how long a message is relevant to the end user.
	If this expires, the message won't continue to be routed.
	Default is infinite.
 
 @param validUntil - Date and time until when message is valid
 */
- (void)setValidityPeriod:(NSDate *)validUntil;

/*! Schedule message to be delivered at a certain time in the future.
	Note Credits will be deducted from your connection at the time of sending
	for the price at that time.
	Therefore we do not encourage delivery dates set long in the future.
 
 @param sendingTime - Date and time when message should be sent
 */
- (void)scheduleSendingAtTime:(NSDate *)sendingTime;

/*! Explicitly set encoding
 
 @param encoding - UTF-8, ISO-8859-15 or Unicode. 
					If omitted, the default charset is UTF-8.
					The unicode uses the UCS2 standard UTF16-BE.
 */
- (void)setEncoding:(NSString *)encoding;

/*! Add groups recipients to axisting message
 
 @param groups - Array of groups to receive message
 */
- (void)addGroupsRecipients:(NSArray *)groups;

/*! Method that performs a dry run of SMS sending
 
 @param message - Message to validate
 @param block - Returns message without ID or error if validation failed
 */
- (void)validateMessageOnCompletion:(void(^)(BSMessage *message, NSArray *errors))block;

@end
