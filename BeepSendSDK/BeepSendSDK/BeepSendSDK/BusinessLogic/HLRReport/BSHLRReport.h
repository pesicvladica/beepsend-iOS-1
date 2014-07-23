//
//  BSHLRReportModel.h
//  BeepSendSDK
//
//  Created by Vladica Pesic on 6/25/14.
//  Copyright (c) 2014 BeepSend. All rights reserved.
//

#import "BSGeneralModel.h"

@interface BSHLRReport : BSGeneralModel

/** When the HLR reached Beepsend.
 */
@property (nonatomic, strong, readonly) NSDate *hlrReachedAt;

/** When HLR response reached Beepsend.
 */
@property (nonatomic, strong, readonly) NSDate *responseReachedAt;

- (BSHLRReport *)initReportWithHLRReachedDate:(NSDate *)rDate
					   andResponseReachedDate:(NSDate *)sDate;

@end

