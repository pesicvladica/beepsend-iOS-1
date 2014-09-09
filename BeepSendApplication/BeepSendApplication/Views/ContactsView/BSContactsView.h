//
//  BSContactsView.h
//  BeepSendApplication
//
//  Created by Vladica Pesic on 7/22/14.
//  Copyright (c) 2014 BeepSend. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface BSContactsView : UIView

@property (nonatomic, strong) UIButton *buttonAddContact;
@property (nonatomic, strong) UIButton *buttonBack;

@property (nonatomic, strong) UITableView *tableViewContacts;

@end