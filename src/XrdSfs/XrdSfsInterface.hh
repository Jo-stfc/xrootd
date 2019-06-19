#include "XrdSfs/XrdSfsGPFInfo.hh"
class  XrdOucTList;
//! Read file bytes using asynchrnous I/O.
virtual XrdSfsXferSize read(XrdSfsAio *aioparm) = 0;
                             int               rdvCnt)
                            {XrdSfsXferSize rdsz, totbytes = 0;
                             for (int i = 0; i < rdvCnt; i++)
                                 {rdsz = read(readV[i].offset,
                                              readV[i].data, readV[i].size);
                                  if (rdsz != readV[i].size)
                                     {if (rdsz < 0) return rdsz;
                                      error.setErrInfo(ESPIPE,"read past eof");
                                      return SFS_ERROR;
                                     }
                                  totbytes += rdsz;
                                 }
                             return totbytes;
                            }
//! Write file bytes using asynchrnous I/O.
                              int               wdvCnt)
                             {XrdSfsXferSize wrsz, totbytes = 0;
                              for (int i = 0; i < wdvCnt; i++)
                                  {wrsz = write(writeV[i].offset,
                                                writeV[i].data, writeV[i].size);
                                   if (wrsz != writeV[i].size)
                                      {if (wrsz < 0) return wrsz;
                                      error.setErrInfo(ESPIPE,"write past eof");
                                      return SFS_ERROR;
                                     }
                                  totbytes += wrsz;
                                 }
                             return totbytes;
                            }
//! @return The bit-wise featue set (i.e. this supported or configured).
//!         See, include file XrdSfsFeatures.hh to actual values.
//-----------------------------------------------------------------------------
//! Copy a file from a remote location to the local file system.
//!
//! @param  fInfo  - getFile() parameters.
//! @param  eInfo  - The object where call-time error info or results are to
//!                  be returned. See return notes.
//! @param  client - Client's identify (see common description). Note that
//!                  client may become invalid after SFS_STARTED is returned.
//!
//! @return One of SFS_DATA, SFS_ERROR, SFS_OK, SFS_REDIRECT, or SFS_STARTED..
//!         The fInfo object is deleted upon return unless SFS_STARTED is
//!         returned. In this case, the fInfo object is deleted only when
//!         fInfo.Completed() is called. The eInfo is deleted upon return.
//-----------------------------------------------------------------------------

virtual int            getFile(      XrdSfsGPFInfo  &fInfo,
                                     XrdOucErrInfo  &eInfo,
                               const XrdSecEntity   *client = 0)
                            {(void)fInfo; (void)client;
                             eInfo.setErrInfo(ENOTSUP, "Not supported.");
                             return SFS_ERROR;
                            }

//! Return directory/file existence information (short stat).
//! @param  path   - Pointer to the path of the file/directory in question.
//! @param  eFlag  - Where the results are to be returned.
//! @param  eInfo  - The object where error info is to be returned.
//! @param  opaque - Path's CGI information (see common description).
//! @return One of SFS_OK, SFS_ERROR, SFS_REDIRECT, SFS_STALL, or SFS_STARTED
//!         When SFS_OK is returned, eFlag must be properly set, as follows:
//!         XrdSfsFileExistNo            - path does not exist
//!         XrdSfsFileExistIsFile        - path refers to an  online file
//!         XrdSfsFileExistIsDirectory   - path refers to an  online directory
//!         XrdSfsFileExistIsOffline     - path refers to an offline file
//!         XrdSfsFileExistIsOther       - path is neither a file nor directory
virtual int            exists(const char                *path,
                                    XrdSfsFileExistence &eFlag,
                                    XrdOucErrInfo       &eInfo,
                              const XrdSecEntity        *client = 0,
                              const char                *opaque = 0) = 0;
//! Copy a file to a remote location to the local file system.
//!
//! @param  fInfo  - putFile() parameters.
//! @param  eInfo  - The object where call-time error info or results are to
//!                  be returned. See return notes.
//! @param  client - Client's identify (see common description). Note that
//!                  client may become invalid after SFS_STARTED is returned.
//!
//! @return One of SFS_DATA, SFS_ERROR, SFS_OK, SFS_REDIRECT, or SFS_STARTED..
//!         The fInfo object is deleted upon return unless SFS_STARTED is
//!         returned. In this case, the fInfo object is deleted only when
//!         fInfo.Completed() is called. The eInfo is deleted upon return.
//-----------------------------------------------------------------------------

virtual int            putFile(      XrdSfsGPFInfo  &fInfo,
                                     XrdOucErrInfo  &eInfo,
                               const XrdSecEntity   *client = 0)
                            {(void)fInfo; (void)client;
                             eInfo.setErrInfo(ENOTSUP, "Not supported.");
                             return SFS_ERROR;
                            }

//-----------------------------------------------------------------------------
//! Preapre a file for future processing.