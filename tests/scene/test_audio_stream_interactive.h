/**************************************************************************/
/*  test_audio_stream_interactive.h                                       */
/**************************************************************************/
/*                         This file is part of:                          */
/*                             GODOT ENGINE                               */
/*                        https://godotengine.org                         */
/**************************************************************************/
/* Copyright (c) 2014-present Godot Engine contributors (see AUTHORS.md). */
/* Copyright (c) 2007-2014 Juan Linietsky, Ariel Manzur.                  */
/*                                                                        */
/* Permission is hereby granted, free of charge, to any person obtaining  */
/* a copy of this software and associated documentation files (the        */
/* "Software"), to deal in the Software without restriction, including    */
/* without limitation the rights to use, copy, modify, merge, publish,    */
/* distribute, sublicense, and/or sell copies of the Software, and to     */
/* permit persons to whom the Software is furnished to do so, subject to  */
/* the following conditions:                                              */
/*                                                                        */
/* The above copyright notice and this permission notice shall be         */
/* included in all copies or substantial portions of the Software.        */
/*                                                                        */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,        */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF     */
/* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY   */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,   */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE      */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                 */
/**************************************************************************/

#ifndef TEST_AUDIO_STREAM_INTERACTIVE_H
#define TEST_AUDIO_STREAM_INTERACTIVE_H

#include "tests/test_macros.h"
#include "../../modules/interactive_music/audio_stream_interactive.h"


TEST_CASE("[AudioStreamInteractive] Set and Get Initial Clip") {
    AudioStreamInteractive audio_stream;

    // Set initial clip and check
    audio_stream.set_clip_count(5);  // Set a valid clip count first
    audio_stream.set_initial_clip(3);
    CHECK(audio_stream.get_initial_clip() == 3);

    // Test invalid clip index (should fail gracefully)
    audio_stream.set_initial_clip(10);  // Clip index exceeds clip count
    CHECK(audio_stream.get_initial_clip() == 3);  // Should still return 3 (no crash)
}

TEST_CASE("[AudioStreamInteractive] Set Clip Name") {
    AudioStreamInteractive audio_stream;

    // Set and check clip name
    audio_stream.set_clip_count(5);  // Set a valid clip count first
    audio_stream.set_clip_name(2, "Clip 2");
    CHECK(audio_stream.get_clip_name(2) == "Clip 2");

    // Test invalid clip index
    audio_stream.set_clip_name(10, "Invalid Clip");
    CHECK(audio_stream.get_clip_name(10) == StringName());  // Should return default empty name
}

TEST_CASE("[AudioStreamInteractive] Set and Get Transition") {
    AudioStreamInteractive audio_stream;

    // Set a clip count and add a transition
    audio_stream.set_clip_count(5);
    audio_stream.add_transition(1, 2, AudioStreamInteractive::TransitionFromTime(0), AudioStreamInteractive::TransitionToTime(10),
                                AudioStreamInteractive::FadeMode(1), 2.0f, true, 3, false);

    // Check if transition exists
    CHECK(audio_stream.has_transition(1, 2) == true);

    // Check transition properties
    CHECK(audio_stream.get_transition_from_time(1, 2) == AudioStreamInteractive::TransitionFromTime(0));
    CHECK(audio_stream.get_transition_to_time(1, 2) == AudioStreamInteractive::TransitionToTime(10));
    CHECK(audio_stream.get_transition_fade_mode(1, 2) == AudioStreamInteractive::FadeMode(1));
    CHECK(audio_stream.get_transition_fade_beats(1, 2) == 2.0f);
}

TEST_CASE("[AudioStreamInteractive] Set Clip Auto Advance") {
    AudioStreamInteractive audio_stream;

    // Set clip count
    audio_stream.set_clip_count(5);

    // Set and check auto advance mode
    audio_stream.set_clip_auto_advance(2, AudioStreamInteractive::AUTO_ADVANCE_NEXT_CLIP);
    CHECK(audio_stream.get_clip_auto_advance(2) == AudioStreamInteractive::AUTO_ADVANCE_NEXT_CLIP);

    // Test invalid clip index (should fail gracefully)
    audio_stream.set_clip_auto_advance(10, AudioStreamInteractive::AUTO_ADVANCE_NEXT_CLIP);
    CHECK(audio_stream.get_clip_auto_advance(10) == AudioStreamInteractive::AUTO_ADVANCE_DISABLED);
}

} // namespace TestAudioStreamInteractive

#endif // TEST_AUDIO_STREAM_INTERACTIVE_H
