//
//  BSRootViewController.m
//  BeepSendApplication
//
//  Created by Vladica Pesic on 6/11/14.
//  Copyright (c) 2014 BeepSend. All rights reserved.
//

#import "BSRootViewController.h"

#import "BSRootView.h"

#import "BSUserTypeTableViewCell.h"
#import "BSConnectionTableViewCell.h"

//TODO: IMPORT SDK FOR TESTING
#import "BSUser.h"
#import "BSConnection.h"

@interface BSRootViewController () <UITableViewDataSource, UITableViewDelegate, UITextFieldDelegate>

@property (nonatomic, weak) UIScrollView *scrollView;

@property (nonatomic, weak) UILabel *labelName;
@property (nonatomic, weak) UILabel *labelEmail;
@property (nonatomic, weak) UILabel *labelPhone;

@property (nonatomic, weak) UITextField *textFieldName;
@property (nonatomic, weak) UITextField *textFieldEmail;
@property (nonatomic, weak) UITextField *textFieldPhone;

@property (nonatomic, weak) UITableView *tableViewUserTypes;

@property (nonatomic, weak) UIButton *buttonDefaultConnection;
@property (nonatomic, weak) UIButton *buttonCustomer;

@property (nonatomic, weak) UIButton *buttonVerifiedTerms;
@property (nonatomic, weak) UIButton *buttonVerifiedPhone;
@property (nonatomic, weak) UIButton *buttonVerifiedEmail;

@property (nonatomic, weak) UITableView *tableViewConnections;

@property (nonatomic, strong) NSArray *dataSourceConnections;

- (void)setupViewElements;

- (void)keyboardBecameActive:(NSNotification *)notification;
- (void)keyboardBecameInactive:(NSNotification *)notification;

- (void)animateScrollViewFrame:(CGRect)newFrame withDuration:(CGFloat)duration andAnimationCurve:(NSInteger)animationCurve;

@end

@implementation BSRootViewController

#pragma mark - Initialization

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

#pragma mark - View lifecycle

- (void)loadView
{
	BSRootView *rootView = [[BSRootView alloc] initWithFrame:[UIScreen mainScreen].bounds];
	
	_scrollView = rootView.scrollViewContainer;
	
	_labelName = rootView.labelName;
	_labelEmail = rootView.labelEmail;
	_labelPhone = rootView.labelPhone;
	
	_textFieldName = rootView.textFieldName;
	_textFieldName.delegate = self;
	_textFieldEmail = rootView.textFieldEmail;
	_textFieldEmail.delegate = self;
	_textFieldPhone = rootView.textFieldPhone;
	_textFieldPhone.delegate = self;
	
	_tableViewUserTypes = rootView.tableViewUserTypes;
	_tableViewUserTypes.dataSource = self;
	_tableViewUserTypes.delegate = self;
	
	_buttonDefaultConnection = rootView.buttonDefaultConnection;
	_buttonCustomer = rootView.buttonCustomer;
	
	_buttonVerifiedEmail = rootView.buttonVerifiedEmail;
	_buttonVerifiedPhone = rootView.buttonVerifiedPhone;
	_buttonVerifiedTerms = rootView.buttonVerifiedTerms;
	
	_tableViewConnections = rootView.tableViewConnections;
	_tableViewConnections.dataSource = self;
	_tableViewConnections.delegate = self;
	
	_tableViewConnections = rootView.tableViewConnections;
	_tableViewConnections.dataSource = self;
	_tableViewConnections.delegate = self;
	
	self.view = rootView;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
    // Do any additional setup after loading the view.
	
	[self setupViewElements];
	
	//Add keyboard appearance notification
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardBecameActive:) name:UIKeyboardWillShowNotification object:nil];
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(keyboardBecameInactive:) name:UIKeyboardWillHideNotification object:nil];
	
	//Collect all available connections for user
	[[BSUser currentUser] getAvailableConnectionsOnCompletion:^(NSArray *connections) {
		_dataSourceConnections = connections;
		[_tableViewConnections reloadData];
	}];
	
	//Reload user types table view
	[_tableViewUserTypes reloadData];
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)dealloc
{
	[[NSNotificationCenter defaultCenter] removeObserver:self name:UIKeyboardWillShowNotification object:nil];
	[[NSNotificationCenter defaultCenter] removeObserver:self name:UIKeyboardWillHideNotification object:nil];
}

#pragma mark - Private methods

- (void)setupViewElements
{
	BSUser *u = [BSUser currentUser];

	_labelName.text = NSLocalizedString(@"Name:", @"");
	_labelEmail.text = NSLocalizedString(@"Email:", @"");
	_labelPhone.text = NSLocalizedString(@"Phone:", @"");
	
	_textFieldName.text = u.name;
	_textFieldEmail.text = u.email;
	_textFieldPhone.text = u.phone;
	
	[_buttonCustomer setTitle:u.customer forState:UIControlStateNormal];
	[_buttonDefaultConnection setTitle:u.defaultConnection.label forState:UIControlStateNormal];
}

- (void)keyboardBecameActive:(NSNotification *)notification
{
	CGRect keyboardFrameEndUser = [notification.userInfo[UIKeyboardFrameEndUserInfoKey] CGRectValue];
	CGRect scrollViewFrame = _scrollView.frame;
	scrollViewFrame.size.height = keyboardFrameEndUser.origin.y;
	
	[self animateScrollViewFrame:scrollViewFrame
					withDuration:[notification.userInfo[UIKeyboardAnimationDurationUserInfoKey] doubleValue]
			   andAnimationCurve:[notification.userInfo[UIKeyboardAnimationCurveUserInfoKey] integerValue]];
}

- (void)keyboardBecameInactive:(NSNotification *)notification
{
	CGRect keyboardFrameEndUser = [notification.userInfo[UIKeyboardFrameEndUserInfoKey] CGRectValue];
	CGRect scrollViewFrame = _scrollView.frame;
	scrollViewFrame.size.height = keyboardFrameEndUser.origin.y;
	
	[self animateScrollViewFrame:scrollViewFrame
					withDuration:[notification.userInfo[UIKeyboardAnimationDurationUserInfoKey] doubleValue]
			   andAnimationCurve:[notification.userInfo[UIKeyboardAnimationCurveUserInfoKey] integerValue]];
}

- (void)animateScrollViewFrame:(CGRect)newFrame withDuration:(CGFloat)duration andAnimationCurve:(NSInteger)animationCurve {
	[UIView beginAnimations:nil context:NULL];
	[UIView setAnimationDuration:duration];
	[UIView setAnimationCurve:animationCurve];
	[UIView setAnimationBeginsFromCurrentState:YES];
	{
		self.view.frame = newFrame;
	}
	[UIView commitAnimations];
}

#pragma mark - UITableView data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
	return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
	if ([tableView isEqual:_tableViewUserTypes]) {
		return [[BSUser currentUser].userTypes count];
	}
	else {
		return [_dataSourceConnections count];
	}
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
	NSString *CellIdentifier;
	if ([tableView isEqual:_tableViewUserTypes]) {
		CellIdentifier = @"UserTypeCell";
	}
	else {
		CellIdentifier = @"ConnectionCell";
	}
	
	UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
	if (!cell) {
		if ([tableView isEqual:_tableViewUserTypes]) {
			cell = [[BSUserTypeTableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
		}
		else {
			cell = [[BSConnectionTableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
		}
	}
	
	if ([tableView isEqual:_tableViewUserTypes]) {
		cell.textLabel.text	= [[BSUser currentUser].userTypes[indexPath.row] title];
	}
	else {
		cell.textLabel.text = [_dataSourceConnections[indexPath.row] title];
	}
	
	return cell;
}

#pragma mark - UITextField delegate

- (BOOL)textFieldShouldReturn:(UITextField *)textField
{
	[textField resignFirstResponder];
	return YES;
}

@end
