//
//  BatchUser.h
//  Batch
//
//  https://batch.com
//  Copyright (c) 2015 Batch SDK. All rights reserved.
//

#import <Foundation/Foundation.h>

@class BatchUserDataEditor;

/*!
 @class BatchUser
 @abstract Provides Batch User functionalities
 @availability from iOS 6.0
 */
@interface BatchUser : NSObject

/*!
 @method init
 @warning This class only has class methods, no need to allocate it yourself.
 */
- (nullable instancetype)init NS_UNAVAILABLE;

/*!
 @method installationID
 @abstract Get the unique installation ID, generated by Batch.
 @discussion You can call this method from any thread.
 @return Batch-generated installation ID. Might be nil if Batch isn't started.
 */
+ (nullable NSString*)installationID;

/*!
 @method editor
 @abstract Get the user data editor
 @discussion Do not forget to call save once you're done changing the attributes
 @discussion You can call this method from any thread.
 @return Batch user data editor
 */
+ (nonnull BatchUserDataEditor*)editor;

/*!
 @method trackEvent:
 @abstract Track an event
 @discussion You can call this method from any thread. Batch must be started at some point, or events won't be sent to the server.
 @param event   : The event name. It should be made of letters, numbers or underscores ([a-z0-9_]) and can't be longer than 30 characters.
 */
+ (void)trackEvent:(nonnull NSString*)event;

/*!
 @method trackEvent:withLabel:
 @abstract Track an event
 @discussion You can call this method from any thread. Batch must be started at some point, or events won't be sent to the server.
 @param event   : The event name. It should be made of letters, numbers or underscores ([a-z0-9_]) and can't be longer than 30 characters.
 @param label   : The event label (optional). Must be a string.
 */
+ (void)trackEvent:(nonnull NSString*)event withLabel:(nullable NSString*)label;

/*!
 @method trackEvent:withLabel:data:
 @abstract Track an event
 @discussion You can call this method from any thread. Batch must be started at some point, or events won't be sent to the server.
 @param event   : The event name. It should be made of letters, numbers or underscores ([a-z0-9_]) and can't be longer than 30 characters.
 @param label   : The event label (optional). Must be a string.
 @param data    : The event data (optional). Must a serializable JSON Foundation dictionary (meaning that it must pass +[NSJSONSerialization isValidJSONObject]'s check). See NSJSONSerialization documentation for supported types, with the only difference that the top level object MUST BE a NSDictionary and not a NSArray.
 */
+ (void)trackEvent:(nonnull NSString*)event withLabel:(nullable NSString*)label data:(nullable NSDictionary*)data;

/*!
 @method trackTransactionWithAmount:
 @abstract Track a transaction
 @discussion You can call this method from any thread. Batch must be started at some point, or events won't be sent to the server.
 @param amount   : Transaction's amount.
 */
+ (void)trackTransactionWithAmount:(double)amount;

/*!
 @method trackTransactionWithAmount:data:
 @abstract Track a transaction
 @discussion You can call this method from any thread. Batch must be started at some point, or events won't be sent to the server.
 @param amount   : Transaction's amount.
 @param data     : The transaction data (optional). Must a serializable JSON Foundation dictionary (meaning that it must pass +[NSJSONSerialization isValidJSONObject]'s check). See NSJSONSerialization documentation for supported types, with the only difference that the top level object MUST BE a NSDictionary and not a NSArray.
 */
+ (void)trackTransactionWithAmount:(double)amount data:(nullable NSDictionary*)data;

/*!
 @method printDebugInformation
 @abstract Print the currently known attributes and tags for a user to the logs (stderr/syslog).
 */
+ (void)printDebugInformation;

@end

@interface BatchUserDataEditor : NSObject

/*!
 @method init
 @warning You should get your instance from BatchUser, rather than instanciating yourself.
 */
- (nullable instancetype)init NS_UNAVAILABLE;

/*!
 @method setLanguage:
 @abstract Override the detected user language.
 @discussion You can call this method from any thread.
 @param language   : Language override: lowercase, ISO 639 formatted string. nil to reset.
 */
- (void)setLanguage:(nullable NSString*)language;

/*!
 @method setRegion:
 @abstract Override the detected user region.
 @discussion You can call this method from any thread.
 @param region   : Region override: uppercase, ISO 3166 formatted string. nil to reset.
 */
- (void)setRegion:(nullable NSString*)region;

/*!
 @method setIdentifier:
 @abstract Set the user identifier.
 @discussion You can call this method from any thread.
 @warning Be careful: you should make sure the identifier uniquely identifies a user. When pushing an identifier, all installations with that identifier will get the Push, which can cause some privacy issues if done wrong. Also affects Unlock offer delivery and restore.
 @param identifier   : User identifier.
 */
- (void)setIdentifier:(nullable NSString*)identifier;

/*!
 @method setAttribute:forKey:
 @abstract Set a custom user attribute for a key
 @discussion You can call this method from any thread.
 @param attribute
    The attribute value. If nil, the attribute will be removed.
 
    The attribute can be one of the following types, or their native Swift equivalent
 
        - NSString
 
            Must not be longer than 64 characters. Can be empty.
 
            For better results, you should make them upper/lowercase and trim the whitespaces.
 
        - NSNumber
 
            Anything bigger than a `long long` or a `double` will be rejected
 
            Unsigned values will be rejected
 
            Booleans are supported, but should be initialized with `[NSNumber numberWithBool:<your value>]` or `@YES/@NO`
 
        - NSDate
 
            Note that since timezones are not supported, this will typically represent UTC dates.
 
    Using any unsupported type as a value (NSNull, NSObject, NSArray, NSDictionary for example) will **NOT** work.
 @param key
    The attribute key. Can't be nil.
 
    It should be made of letters, numbers or underscores ([a-z0-9_]) and can't be longer than 30 characters.
 */
- (void)setAttribute:(nullable NSObject*)attribute forKey:(nonnull NSString*)key;

/*!
 @method removeAttributeForKey:
 @abstract Removes an attribute for the specified key.
 @discussion You can call this method from any thread.
 @param key The attribute key. Can't be nil.
 */
- (void)removeAttributeForKey:(nonnull NSString*)key;

/*!
 @method clearAttributes
 @abstract Removes all custom attributes.
 @discussion You can call this method from any thread.
 @warning Once applied, this action cannot be undone.
 */
- (void)clearAttributes;

/*!
 @method addTag:inCollection:
 @abstract Add a tag to the specified collection. If empty, the collection will be created automatically.
 @discussion You can call this method from any thread.
 @param tag The tag to add. Cannot be nil or empty. Must be a string no longer than 64 characters.
 @param collection The tag collection name. Cannot be nil. Must be a string of letters, numbers or underscores ([a-z0-9_]) and can't be longer than 30 characters.
 */
- (void)addTag:(nonnull NSString*)tag inCollection:(nonnull NSString*)collection;

/*!
 @method removeTag:fromCollection:
 @abstract Removes a tag from the specified collection.
 @discussion You can call this method from any thread.
 @param tag The tag to remove. Cannot be nil. If the tag doesn't exist, this method will do nothing.
 @param collection The tag collection name. Cannot be nil. Must be a string of letters, numbers or underscores ([a-z0-9_]) and can't be longer than 30 characters. If the collection doesn't exist, this method will do nothing, but apply won't fail.
 */
- (void)removeTag:(nonnull NSString*)tag fromCollection:(nonnull NSString*)collection;

/*!
 @method clearTags:
 @abstract Removes all tags.
 @discussion You can call this method from any thread.
 @warning Once applied, this action cannot be undone.
 */
- (void)clearTags;

/*!
 @method clearTagCollection:
 @abstract Removes all tags from a collection.
 @discussion You can call this method from any thread.
 @warning Once applied, this action cannot be undone.
 @param collection The tag collection name. Cannot be nil. Must be a string of letters, numbers or underscores ([a-z0-9_]) and can't be longer than 30 characters.
 */
- (void)clearTagCollection:(nonnull NSString*)collection;

/*!
 @method save
 @abstract Save all of the pending changes made in that editor.
 @discussion You can call this method from any thread.
 @warning This action cannot be undone.
 */
- (void)save;

@end