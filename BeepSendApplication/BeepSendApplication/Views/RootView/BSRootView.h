//
//  BSRootView.h
//  BeepSendApplication
//
//  Created by Vladica Pesic on 6/11/14.
//  Copyright (c) 2014 BeepSend. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "BSTextFieldCustomTextInset.h"

@interface BSRootView : UIView

@property (nonatomic, strong) UIScrollView *scrollViewContainer;

@property (nonatomic, strong) UILabel *labelName;
@property (nonatomic, strong) UILabel *labelEmail;
@property (nonatomic, strong) UILabel *labelPhone;

@property (nonatomic, strong) BSTextFieldCustomTextInset *textFieldName;
@property (nonatomic, strong) BSTextFieldCustomTextInset *textFieldEmail;
@property (nonatomic, strong) BSTextFieldCustomTextInset *textFieldPhone;

@property (nonatomic, strong) UITableView *tableViewUserTypes;

@property (nonatomic, strong) UIButton *buttonDefaultConnection;
@property (nonatomic, strong) UIButton *buttonCustomer;

@property (nonatomic, strong) UIButton *buttonVerifiedTerms;
@property (nonatomic, strong) UIButton *buttonVerifiedPhone;
@property (nonatomic, strong) UIButton *buttonVerifiedEmail;

@property (nonatomic, strong) UITableView *tableViewConnections;

@end
