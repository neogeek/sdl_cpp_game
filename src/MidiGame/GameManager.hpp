#pragma once

#include "Handcrank/Handcrank.hpp"

#include <CoreFoundation/CoreFoundation.h>
#include <CoreMIDI/CoreMIDI.h>
#include <iostream>

using namespace Handcrank;

void MyMIDIReadProc(const MIDIPacketList *pktlist, void *readProcRefCon,
                    void *srcConnRefCon)
{
    const MIDIPacket *packet = &pktlist->packet[0];
    for (unsigned int i = 0; i < pktlist->numPackets; i++)
    {
        for (unsigned int j = 0; j < packet->length; j += 3)
        {
            uint8_t status = packet->data[j];
            uint8_t note = packet->data[j + 1];
            uint8_t velocity = packet->data[j + 2];

            if ((status & 0xF0) == 0x90 && velocity > 0)
            {
                std::cout << "Note On: " << static_cast<int>(note) << std::endl;
            }
            else if ((status & 0xF0) == 0x80 ||
                     ((status & 0xF0) == 0x90 && velocity == 0))
            {
                std::cout << "Note Off: " << static_cast<int>(note)
                          << std::endl;
            }
        }
        packet = MIDIPacketNext(packet);
    }
}

MIDIClientRef client;
MIDIPortRef inputPort;

class GameManager : public RenderObject
{

  public:
    void Start() override
    {

        game->SetTitle("MidiGame");

        MIDIClientCreate(CFSTR("MIDI Client"), nullptr, nullptr, &client);
        MIDIInputPortCreate(client, CFSTR("Input Port"), MyMIDIReadProc,
                            nullptr, &inputPort);

        unsigned long sourceCount = MIDIGetNumberOfSources();

        for (unsigned long i = 0; i < sourceCount; ++i)
        {
            MIDIEndpointRef source = MIDIGetSource(i);
            MIDIPortConnectSource(inputPort, source, nullptr);
        }

        CFRunLoopRun();
    }
};
