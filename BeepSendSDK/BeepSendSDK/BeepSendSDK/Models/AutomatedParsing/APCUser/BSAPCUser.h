//
//  APCUser.h
//  BeepSendSDK
//
//  Created by Vladica Pesic on 6/19/14.
//  Copyright (c) 2014 BeepSend. All rights reserved.
//

#import "BSSerializableObject.h"

#import "BSAPConnection.h"
#import "BSAPVerified.h"

#import "BSUserModel.h"

@interface BSAPCUser : BSSerializableObject

@property (nonatomic, strong) NSString *id;
@property (nonatomic, strong) NSString *name;
@property (nonatomic, strong) NSString *username;

@property (nonatomic, strong) NSString *email;
@property (nonatomic, strong) NSString *phone;
@property (nonatomic, strong) NSString *customer;
@property (nonatomic, strong) NSString *api_token;
@property (nonatomic, strong) BSAPConnection *default_connection;
@property (nonatomic, strong) NSArray *user_types;
@property (nonatomic, strong) NSNumber *max_level;
@property (nonatomic, strong) BSAPVerified *verified;

+ (NSArray *)arrayOfObjectsFromArrayOfDictionaries:(NSArray *)array;

- (BSUserModel *)convertToUserModel;

@end
