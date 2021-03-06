//
//  MCTimeBase.h
//  iOS Midi Tester
//
//  Created by Olivier Scherler on 07.12.12.
//  Copyright (c) 2012 Olivier Scherler. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreMIDI/CoreMIDI.h>
#import <mach/mach_time.h>

// redefine a MIDIPacket struct for the clock, with just 1 byte of data, so we ca take its sizeof
struct ClockMIDIPacketStruct {
	MIDITimeStamp  timeStamp;
	UInt16         length;
	Byte           data[1];
};
typedef struct ClockMIDIPacketStruct ClockMIDIPacket;

#define MC_CLOCK_PACKET_SIZE        sizeof( ClockMIDIPacket )
#define MC_PACKET_LIST_HEADER_SIZE  sizeof( UInt32 )

#define MC_DEFAULT_TEMPO      120
#define MC_CLOCKS_PER_BEAT     24

@interface MCTimeBase : NSObject
{
	double ticks_per_second;
	double ticks_in_clock;
	UInt32 current_clock;
}

@property (nonatomic, assign, setter = setTempo:) UInt32 tempo;
@property (assign) UInt64 start_time;

- (id) initWithTempo: (UInt32) new_tempo;
- (double) clocksPerSecondForTempo: (UInt32) new_tempo;

- (void) start;
- (void) stop;
- (BOOL) isStarted;
- (UInt64) nextClock;
- (UInt64) ticksToNextClock;
- (UInt64) clockTicks;
- (double) ticksPerSecond;
- (UInt64) beatTicks;
- (MIDIPacketList *) clocksForDuration: (UInt32) ms;

@end
