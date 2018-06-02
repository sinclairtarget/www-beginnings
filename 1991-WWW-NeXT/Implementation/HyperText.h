//			HyperText Class
//

#import <appkit/Text.h>
#import <objc/List.h>
#import "Anchor.h"
#import "HTStyle.h"

/*	Bit fields describing the capabilities of a node:
*/
#define HT_READ			1
#define HT_WRITE		2
#define HT_LINK_TO_NODE		4
#define HT_LINK_TO_PART		8
#define HT_LINK_FROM_NODE	16
#define HT_LINK_FROM_PART	32
#define HT_DO_ANYTHING		63

extern void write_rtf_header(NXStream* rtfStream);
extern HyperAccess * HTAccMgr;

@interface HyperText:Text
{
	Anchor * nodeAnchor;	//	An anchor representing the node
	int	nextAnchorNumber; //	The serial number of the next anchor
	int	protection;	//	Server capability authorised
	BOOL	isIndex;	//	Can accept a keyword search
	int	slotNumber;	//	Window display position
	int	format;		//	See WWW.h for values
}

+ newAnchor:(Anchor*)anAnchor;

- readSGML:(NXStream*)sgmlStream diagnostic:(int)diagnostic;
- writeSGML:(NXStream*)sgmlStream relativeTo:(const char *)aName;

- readText:(NXStream*)stream;	//	Overrides Text's method.
- Accmgr;
- (BOOL) isIndex;
- setupWindow;
- adjustWindow;			// Adust scroll bars, sizeability, size, etc.

- (int) format;
- setFormat:(int)format;

//	Style handling:

- applyToSimilar: (HTStyle *)style;	// Apply this style to the selection
- applyStyle: (HTStyle *)style;		// Apply this style to the selection
- selectUnstyled: (HTStyleSheet *)sheet;// Select the first unstyled run.
- updateStyle: (HTStyle *)style;	// Update all text with changed style.
- (HTStyle *)selectionStyle:(HTStyleSheet*)sheet; // style if any of  selection
- replaceSel:(const char *)aString style:(HTStyle*)aStyle; // Paste in styled text

//	"Fast" Methods for external parsers:

- appendBegin;				// Start an append sequence
- appendStyle:(HTStyle *) style;	// Set the style for future text
- appendText: (const char *)text;	// Add a string
- appendCharacter: (char)ch;	// Add a string
- appendBeginAnchor: (HTAnchor *)a;	// Begin an anchor
- appendEndAnchor;			// End it
- appendEnd;				// Flush out all additions so far


//	Anchor handling:


//- anchors;				// Set of anchors
- nodeAnchor;				// Single anchor representing this node
- followLink;				// (If selected)
- unlinkSelection;			// Remove anchor info from selection
- (Anchor *) referenceSelected;		// Generate anchor for this node
- (Anchor *) referenceAll;
- (Anchor *) linkSelTo: (Anchor*)anchor;// Link selected text to this anchor.
- disconnectAnchor: (Anchor*)anchor;	// Remove reference from this node.
- selectAnchor: (Anchor*)anchor;	// Bring to front and highlight it.

- setTitle:(char *)title;
- dump: sender;			// diagnostic output

//	Override methods of superclasses:

- readText: (NXStream *)stream;		// Also set format variable.
- readRichText: (NXStream *)stream;	// Also set format variable.
- mouseDown:(NXEvent*)theEvent;		// Double click become hyperjump
- keyDown:(NXEvent*)theEvent;		//
- paste:sender;				//

//	Window delegate methods:

- windowDidBecomeMain:sender;

@end
