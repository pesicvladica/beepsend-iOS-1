//
//  BSSerializableObject.m
//  BeepSendSDK
//
//  Created by Vladica Pesic on 6/13/14.
//  Copyright (c) 2014 BeepSend. All rights reserved.
//

#import "BSSerializableObject.h"
#import <objc/runtime.h>

@implementation BSSerializableObject


/**
 * Method that should be called for converting. Override this method if you want to change 
 * whole logic that does the pasing.
 *
 **/
- (NSDictionary *)dictionaryFromClass
{
	return [self dictFromClass:self];
}

/**
 * Method that determins if class inherits from HTSerialazibleObject and calls proper method.
 *
 **/
- (id)dictFromClass:(BSSerializableObject *)object
{
	////////////////////////////////////////////////////////////
	//if class inherits from HTSerialazibleObject class call its
	// dictFromClass method in case overriden
	if([[object class] isSubclassOfClass:[BSSerializableObject class]])
	{
		return [object  dictFromClass];
	}
	else
	{
		return [BSSerializableObject dictFromClass:object];
	}
}

/**
 * Method that does actual conversion. You should override this method if you want custom
 * custom parsing for subclasses.
 *
 **/
- (id)dictFromClass
{
	return [BSSerializableObject dictFromClass:self];
}

/**
 * Class method used for parsing if class being converted does not inherit from HTSerialazibleObject
 *
 **/
+ (id)dictFromClass:(id)classForDict
{
	
	id dict;
	///////////////////////////////////////////////////////////////////////////////////
	//if class is an array parse every element in case they contain classes, arrays etc
	if([classForDict isKindOfClass:[NSArray class]])
	{
		dict = [@[] mutableCopy];
		for (id node in classForDict)
		{
			[dict addObject:[BSSerializableObject dictFromClass:node]];
		}
		return dict;
	}
	else
	{
		dict = [@{} mutableCopy];
		NSArray *propertyList = [BSSerializableObject propetyListForClass:classForDict];
		///////////////////////////////////////////////////////////////
		//if class has no properties it is primitive and just return it
		if(propertyList.count == 0)
		{
			return classForDict;
		}
		
		///////////////////////////////////////////////////////
		//check value for every property and add it to response
		for (NSString *zz in propertyList) {
			if([classForDict valueForKey:zz])
			{
				id value = [BSSerializableObject dictFromClass:[classForDict valueForKey:zz]];
				if (value) {
					if ([value respondsToSelector:@selector(count)]) {
						if ([value count]) {
							[dict setObject:value forKey:zz];
						}
					}
					else {
						[dict setObject:value forKey:zz];
					}
				}
			}
		}
		return dict;
	}
	
}

- (id)convertToModel {
	return nil;
}

/**
 * Method that returns class, or array of classes from the given dict.
 *
 **/
+ (id)classFromDict:(NSDictionary *)dictionary
{
	return [self classFromDict:dictionary withClass:[self class]];
}

/**
 * Method that returns class, or array of klass type objects from the given dict.
 *
 **/
+ (id)classFromDict:(id)dictionary withClass:(Class)klass
{
	////////////////////////////////////////////////////////
	//if dictionary is an array, return array of given types
	if([dictionary isKindOfClass:[NSArray class]])
	{
		NSMutableArray *results = [@[] mutableCopy];
		for (id node in dictionary)
		{
			[results addObject:[self classFromDict:node withClass:klass]];
		}
		return results;
	}
	else
	{
		NSArray *propertyList = [BSSerializableObject propetyListForClass:klass];
		
		if(propertyList.count ==0)
		{
			return dictionary;
		}
		else
		{
			NSDictionary *propetyTypes = [BSSerializableObject classPropsFor:klass];
			NSObject *object = [[klass alloc] init];
			
			if(object)
			{
				///////////////////////////////////////////////////////
				//check value for every property and add it to response
				for (NSString *zz in propertyList) {
					if (![dictionary isKindOfClass:[NSDictionary class]]) {
						return nil;
					}
					if([dictionary objectForKey:zz])
					{
						NSString *className = propetyTypes[zz];
						Class class1 = NSClassFromString(className);
						
						if([class1 isSubclassOfClass:[BSSerializableObject class]])
						{
							////////////////////////////////////////////
							//if implements serialazible call recursivly
							[object setValue:[self classFromDict:dictionary[zz] withClass:NSClassFromString(propetyTypes[zz])] forKey:zz];
						}
//						else if ([class1 isSubclassOfClass:[NSArray class]])
//						{
//							///////////////////////
//							//Array
//							NSMutableArray *results = [@[] mutableCopy];
//							for (id obj in dictionary[zz]) {
//								[results addObject:[self classFromDict:obj withClass:class1]];
//							}
//							[object setValue:[NSArray arrayWithArray:results] forKeyPath:zz];
//						}
						else
						{
							///////////////
							//else just add
							[object setValue:dictionary[zz] forKey:zz];
						}
					}
				}
			}
			
			return object;
		}
	}
}

#pragma mark - Property methods

/**
 * Method used for getting list of propety names for a given class
 *
 **/

+ (NSArray *)propetyListForClass:(id)classToExtractPropertyFrom
{
	unsigned int propertyCount = 0;
	objc_property_t * properties = class_copyPropertyList([classToExtractPropertyFrom class], &propertyCount);
	
	NSMutableArray * propertyNames = [NSMutableArray array];
	for (unsigned int i = 0; i < propertyCount; ++i) {
		objc_property_t property = properties[i];
		const char * name = property_getName(property);
		[propertyNames addObject:[NSString stringWithUTF8String:name]];
	}
	free(properties);
	return propertyNames;
}

/**
 * Method that returns type for given property name
 *
 **/
static const char * getPropertyType(objc_property_t property) {
    const char *attributes = property_getAttributes(property);
    //printf("attributes=%s\n", attributes);
    char buffer[1 + strlen(attributes)];
    strcpy(buffer, attributes);
    char *state = buffer, *attribute;
    while ((attribute = strsep(&state, ",")) != NULL) {
        if (attribute[0] == 'T' && attribute[1] != '@') {
            // it's a C primitive type:
            /*
			 if you want a list of what will be returned for these primitives, search online for
			 "objective-c" "Property Attribute Description Examples"
			 apple docs list plenty of examples of what you get for int "i", long "l", unsigned "I", struct, etc.
			 */
            return (const char *)[[NSData dataWithBytes:(attribute + 1) length:strlen(attribute) - 1] bytes];
        }
        else if (attribute[0] == 'T' && attribute[1] == '@' && strlen(attribute) == 2) {
            // it's an ObjC id type:
            return "id";
        }
        else if (attribute[0] == 'T' && attribute[1] == '@') {
            // it's another ObjC object type:
            return (const char *)[[NSData dataWithBytes:(attribute + 3) length:strlen(attribute) - 4] bytes];
        }
    }
    return "";
}

/**
 * Method that returns property names and types for a given class
 *
 **/
+ (NSDictionary *)classPropsFor:(Class)klass
{
    if (klass == NULL) {
        return nil;
    }
	
    NSMutableDictionary *results = [[NSMutableDictionary alloc] init] ;
	
    unsigned int outCount, i;
    objc_property_t *properties = class_copyPropertyList(klass, &outCount);
    for (i = 0; i < outCount; i++) {
        objc_property_t property = properties[i];
        const char *propName = property_getName(property);
        if(propName) {
			// const char *propType = getPropertyType(property);
            NSString *propertyName = [NSString stringWithUTF8String:propName];
			NSString *propertyType = [NSString stringWithUTF8String:getPropertyType(property)];
			if([BSHelper isNilOrEmpty:propertyType])
			{
				propertyType = [NSString stringWithFormat:@"%s",getPropertyType(property)];
			}
            [results setObject:propertyType forKey:propertyName];
        }
    }
    free(properties);
	
    // returning a copy here to make sure the dictionary is immutable
    return [NSDictionary dictionaryWithDictionary:results];
}

@end
