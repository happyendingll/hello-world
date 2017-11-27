//
//  MyTableViewCell.h
//  attribute
//
//  Created by 曾志远 on 2017/11/27.
//  Copyright © 2017年 曾志远. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface MyTableViewCell : UITableViewCell
@property (weak, nonatomic) IBOutlet UIImageView *imageview;
@property (weak, nonatomic) IBOutlet UILabel *txtname;
@property (weak, nonatomic) IBOutlet UILabel *txtxontent;

@end
