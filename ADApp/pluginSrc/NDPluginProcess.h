#ifndef NDPluginProcess_H
#define NDPluginProcess_H

#include <epicsTypes.h>
#include <asynStandardInterfaces.h>

#include "NDPluginDriver.h"

/* Background array subtraction */
#define NDPluginProcessSaveBackgroundString     "SAVE_BACKGROUND"   /* (asynInt32,   r/w) Save the current frame as background */
#define NDPluginProcessEnableBackgroundString   "ENABLE_BACKGROUND" /* (asynInt32,   r/w) Enable background subtraction? */
#define NDPluginProcessValidBackgroundString    "VALID_BACKGROUND"  /* (asynInt32,   r/o) Is there a valid background */

/* Flat field normalization */
#define NDPluginProcessSaveFlatFieldString      "SAVE_FLAT_FIELD"   /* (asynInt32,   r/w) Save the current frame as flat field */
#define NDPluginProcessEnableFlatFieldString    "ENABLE_FLAT_FIELD" /* (asynInt32,   r/w) Enable flat field normalization? */
#define NDPluginProcessValidFlatFieldString     "VALID_FLAT_FIELD"  /* (asynInt32,   r/o) Is there a valid flat field */
#define NDPluginProcessScaleFlatFieldString     "SCALE_FLAT_FIELD"  /* (asynInt32,   r/o) Scale factor after dividing by flat field */

/* High and low clipping */
#define NDPluginProcessLowClipString            "LOW_CLIP"          /* (asynFloat64, r/w) Low clip value */
#define NDPluginProcessEnableLowClipString      "ENABLE_LOW_CLIP"   /* (asynInt32,   r/w) Enable low clipping? */
#define NDPluginProcessHighClipString           "HIGH_CLIP"         /* (asynFloat64, r/w) High clip value */
#define NDPluginProcessEnableHighClipString     "ENABLE_HIGH_CLIP"  /* (asynInt32,   r/w) Enable high clipping? */
    
/* Recursive filter */
#define NDPluginProcessEnableFilterString       "ENABLE_FILTER"     /* (asynInt32,   r/w) Enable frame filtering? */
#define NDPluginProcessNumFilterString          "NUM_FILTER"        /* (asynInt32,   r/w) Number of frames to filter */
#define NDPluginProcessNumFilteredString        "NUM_FILTERED"      /* (asynInt32,   r/o) Number of frames filtered */
#define NDPluginProcessOC0String                "FILTER_OC0"        /* (asynFloat64, r/w) Output coefficient 0 */
#define NDPluginProcessOC1String                "FILTER_OC1"        /* (asynFloat64, r/w) Output coefficient 1 */
#define NDPluginProcessOC2String                "FILTER_OC2"        /* (asynFloat64, r/w) Output coefficient 2 */
#define NDPluginProcessOC3String                "FILTER_OC3"        /* (asynFloat64, r/w) Output coefficient 3 */
#define NDPluginProcessOC4String                "FILTER_OC4"        /* (asynFloat64, r/w) Output coefficient 4 */
#define NDPluginProcessFC0String                "FILTER_FC0"        /* (asynFloat64, r/w) Filter coefficient 0 */
#define NDPluginProcessFC1String                "FILTER_FC1"        /* (asynFloat64, r/w) Filter coefficient 1 */
#define NDPluginProcessFC2String                "FILTER_FC2"        /* (asynFloat64, r/w) Filter coefficient 2 */
#define NDPluginProcessFC3String                "FILTER_FC3"        /* (asynFloat64, r/w) Filter coefficient 3 */
#define NDPluginProcessFC4String                "FILTER_FC4"        /* (asynFloat64, r/w) Filter coefficient 4 */
#define NDPluginProcessRC0String                "FILTER_RC0"        /* (asynFloat64, r/w) Filter coefficient 5 */
#define NDPluginProcessRC1String                "FILTER_RC1"        /* (asynFloat64, r/w) Filter coefficient 6 */

/* Output data type */
#define NDPluginProcessDataTypeString           "PROCESS_DATA_TYPE" /* (asynInt32,   r/w) Output type.  -1 means automatic. */
   

/** Does image processing operations.  These include
  * Background subtraction
  * Flat field normalization
  * Low clipping
  * High clipping
  * Frame averaging */
class NDPluginProcess : public NDPluginDriver {
public:
    NDPluginProcess(const char *portName, int queueSize, int blockingCallbacks, 
                 const char *NDArrayPort, int NDArrayAddr,
                 int maxBuffers, size_t maxMemory,
                 int priority, int stackSize);
    /* These methods override the virtual methods in the base class */
    void processCallbacks(NDArray *pArray);
    asynStatus writeInt32(asynUser *pasynUser, epicsInt32 value);
    
protected:
    /* Background array subtraction */
    int NDPluginProcessSaveBackground;
    #define FIRST_NDPLUGIN_PROCESS_PARAM NDPluginProcessSaveBackground
    int NDPluginProcessEnableBackground;
    int NDPluginProcessValidBackground;

    /* Flat field normalization */
    int NDPluginProcessSaveFlatField;
    int NDPluginProcessEnableFlatField;
    int NDPluginProcessValidFlatField;
    int NDPluginProcessScaleFlatField;

    /* High and low clipping */
    int NDPluginProcessLowClip;
    int NDPluginProcessEnableLowClip;
    int NDPluginProcessHighClip;
    int NDPluginProcessEnableHighClip;

    /* Frame filtering */
    int NDPluginProcessEnableFilter;
    int NDPluginProcessNumFilter;
    int NDPluginProcessNumFiltered;
    int NDPluginProcessOC0;
    int NDPluginProcessOC1;
    int NDPluginProcessOC2;
    int NDPluginProcessOC3;
    int NDPluginProcessOC4;
    int NDPluginProcessFC0;
    int NDPluginProcessFC1;
    int NDPluginProcessFC2;
    int NDPluginProcessFC3;
    int NDPluginProcessFC4;
    int NDPluginProcessRC0;
    int NDPluginProcessRC1;
    
    /* Output data type */
    int NDPluginProcessDataType;

    #define LAST_NDPLUGIN_PROCESS_PARAM NDPluginProcessDataType
                                
private:
    NDArray *pBackground;
    int     newBackground;
    int     nBackgroundElements;
    NDArray *pFlatField;
    int     newFlatField;
    int     nFlatFieldElements;
    NDArray *pFilter;
    int     newFilter;
    int     numFiltered;
};
#define NUM_NDPLUGIN_PROCESS_PARAMS (&LAST_NDPLUGIN_PROCESS_PARAM - &FIRST_NDPLUGIN_PROCESS_PARAM + 1)
    
#endif