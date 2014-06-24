//
//  APCUser.m
//  BeepSendSDK
//
//  Created by Vladica Pesic on 6/19/14.
//  Copyright (c) 2014 BeepSend. All rights reserved.
//

#import "BSAPCUser.h"

#import "BSAPUserType.h"

#import "BSUserTypeModel.h"

@implementation BSAPCUser

#pragma mark - Inherited methods

+ (id)classFromDict:(NSDictionary *)dictionary
{
	if (![dictionary isKindOfClass:[NSDictionary class]]) {
		return nil;
	}
	
	//We need to register all classes before load
	[BSAPConnection class];
	[BSAPVerified class];
	
	BSAPCUser *user = [super classFromDict:dictionary];
	
	user.user_types = [BSAPUserType arrayOfObjectsFromArrayOfDictionaries:user.user_types];
	
	return user;
}

#pragma mark - Public methods

+ (NSArray *)arrayOfObjectsFromArrayOfDictionaries:(NSArray *)array
{
	NSMutableArray *results = [@[] mutableCopy];
	for (id object in array) {
		[results addObject:[BSAPCUser classFromDict:object]];
	}
	return [NSArray arrayWithArray:results];
}

- (BSUserModel *)convertToUserModel
{
	BSVerifiedModel *verified =
	[[BSVerifiedModel alloc] initUserWithEmailVerified:[_verified.email boolValue]
										 phoneVerified:[_verified.phone boolValue]
										 termsVerified:[_verified.terms boolValue]];
	
	BSConnectionModel *connection =
	[[BSConnectionModel alloc] initConnectionWithID:_default_connection.id
											  label:_default_connection.label
										   systemID:_default_connection.system_id
											   type:_default_connection.type];
	
	NSMutableArray *mUserTypes = [@[] mutableCopy];
	for (BSAPUserType *uType in _user_types) {
		BSUserTypeModel *userType = [[BSUserTypeModel alloc] initUserTypeWithID:uType.id
																		   name:uType.name];
		[mUserTypes addObject:userType];
	}
	
	BSUserModel *usrModel =
	[[BSUserModel alloc] initUserWithID:_id
								   name:_name
								  email:_email
								  phone:_phone
							   customer:_customer
							   apiToken:_api_token
					  defaultConnection:connection
							  userTypes:[NSArray arrayWithArray:mUserTypes]
							   maxLevel:_max_level
							   verified:verified];
	
	return usrModel;
}

@end
