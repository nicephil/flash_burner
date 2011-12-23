/***********************license start***************
 * Copyright (c) 2003-2007, Cavium Networks. All rights reserved.
 * 
 * This software file (the "File") is owned and distributed by Cavium 
 * Networks ("Cavium") under the following dual licensing option: The dual 
 * licensing option gives you, the licensee, the choice between the following 
 * alternative licensing terms.  Once you have made an election to use the 
 * File under one of the following alternative licensing terms (license 
 * types) you are bound by the respective terms and you may distribute the 
 * file (or any derivative thereof), to the extent allowed by the respective 
 * licensing term, only if you (i) delete this introductory statement 
 * regarding the dual licensing option from the file you will distribute, 
 * (ii) delete the licensing term that you have elected NOT to use from the 
 * file you will distribute and (iii) follow the respective licensing term 
 * that you have elected to use with respect to the correct attribution or 
 * licensing term that you have to include with your distribution.  
 * 
 * ***
 * OCTEON SDK License Type 2:
 * 
 * IMPORTANT: Read this Agreement carefully before clicking on the "I accept" 
 * button to download the Software and/or before using the Software.  This 
 * License Agreement (the "Agreement") is a legal agreement between you, 
 * either an individual or a single legal entity ("You" or "you"), and Cavium 
 * Networks ("Cavium").  This Agreement governs your use of the Cavium 
 * software that can be downloaded after accepting this Agreement and/or that 
 * is accompanied by this Agreement (the "Software").  You must accept the 
 * terms of this Agreement before downloading and/or using the Software.  By 
 * clicking on the "I accept" button to download and/or by using the 
 * Software, you are indicating that you have read and understood, and assent 
 * to be bound by, the terms of this Agreement.  If you do not agree to the 
 * terms of the Agreement, you are not granted any rights whatsoever in the 
 * Software.  If you are not willing to be bound by these terms and 
 * conditions, you should not use or cease all use of the Software.  This 
 * Software is the property of Cavium Networks and constitutes the 
 * proprietary information of Cavium Networks.  You agree to take reasonable 
 * steps to prevent the disclosure, unauthorized use or unauthorized 
 * distribution of the Software to any third party.  
 * 
 * License Grant.  Subject to the terms and conditions of this Agreement, 
 * Cavium grants you a nonexclusive, non-transferable, worldwide, fully-paid 
 * and royalty-free license to 
 * 
 * (a) install, reproduce, and execute the executable version of the Software 
 * solely for your internal use and only (a) on hardware manufactured by 
 * Cavium, or (b) software of Cavium that simulates Cavium hardware; 
 * 
 * (b) create derivative works of any portions of the Software provided to 
 * you by Cavium in source code form, which portions enable features of the 
 * Cavium hardware products you or your licensees are entitled to use, 
 * provided that any such derivative works must be used only (a) on hardware 
 * manufactured by Cavium, or (b) software of Cavium that simulates Cavium 
 * hardware; and 
 * 
 * (c) distribute derivative works you created in accordance with clause (b) 
 * above, only in executable form and only if such distribution (i) 
 * reproduces the copyright notice that can be found at the very end of this 
 * Agreement and (ii) is pursuant to a binding license agreement that 
 * contains terms no less restrictive and no less protective of Cavium than 
 * this Agreement.  You will immediately notify Cavium if you become aware of 
 * any breach of any such license agreement.  
 * 
 * Restrictions.  The rights granted to you in this Agreement are subject to 
 * the following restrictions: Except as expressly set forth in this 
 * Agreement (a) you will not license, sell, rent, lease, transfer, assign, 
 * display, host, outsource, disclose or otherwise commercially exploit or 
 * make the Software, or any derivatives you create under this Agreement, 
 * available to any third party; (b) you will not modify or create derivative 
 * works of any part of the Software; (c) you will not access or use the 
 * Software in order to create similar or competitive products, components, 
 * or services; and (d), no part of the Software may be copied (except for 
 * the making of a single archival copy), reproduced, distributed, 
 * republished, downloaded, displayed, posted or transmitted in any form or 
 * by any means.  
 * 
 * Ownership.  You acknowledge and agree that, subject to the license grant 
 * contained in this Agreement and as between you and Cavium (a) Cavium owns 
 * all copies of and intellectual property rights to the Software, however 
 * made, and retains all rights in and to the Software, including all 
 * intellectual property rights therein, and (b) you own all the derivate 
 * works of the Software created by you under this Agreement, subject to 
 * Cavium's rights in the Software.  There are no implied licenses under this 
 * Agreement, and any rights not expressly granted to your hereunder are 
 * reserved by Cavium.  You will not, at any time, contest anywhere in the 
 * world Cavium's ownership of the intellectual property rights in and to the 
 * Software.  
 * 
 * Disclaimer of Warranties.  The Software is provided to you free of charge, 
 * and on an "As-Is" basis.  Cavium provides no technical support, warranties 
 * or remedies for the Software.  Cavium and its suppliers disclaim all 
 * express, implied or statutory warranties relating to the Software, 
 * including but not limited to, merchantability, fitness for a particular 
 * purpose, title, and non-infringement.  Cavium does not warrant that the 
 * Software and the use thereof will be error-free, that defects will be 
 * corrected, or that the Software is free of viruses or other harmful 
 * components.  If applicable law requires any warranties with respect to the 
 * Software, all such warranties are limited in duration to thirty (30) days 
 * from the date of download or first use, whichever comes first.  
 * 
 * Limitation of Liability.  Neither Cavium nor its suppliers shall be 
 * responsible or liable with respect to any subject matter of this Agreement 
 * or terms or conditions related thereto under any contract, negligence, 
 * strict liability or other theory (a) for loss or inaccuracy of data or 
 * cost of procurement of substitute goods, services or technology, or (b) 
 * for any indirect, incidental or consequential damages including, but not 
 * limited to loss of revenues and loss of profits.  Cavium's aggregate 
 * cumulative liability hereunder shall not exceed the greater of Fifty U.S.  
 * Dollars (U.S.$50.00) or the amount paid by you for the Software that 
 * caused the damage.  Certain states and/or jurisdictions do not allow the 
 * exclusion of implied warranties or limitation of liability for incidental 
 * or consequential damages, so the exclusions set forth above may not apply 
 * to you.  
 * 
 * Basis of Bargain.  The warranty disclaimer and limitation of liability set 
 * forth above are fundamental elements of the basis of the agreement between 
 * Cavium and you.  Cavium would not provide the Software without such 
 * limitations.  The warranty disclaimer and limitation of liability inure to 
 * the benefit of Cavium and Cavium's suppliers.  
 * 
 * Term and Termination.  This Agreement and the licenses granted hereunder 
 * are effective on the date you accept the terms of this Agreement, download 
 * the Software, or use the Software, whichever comes first, and shall 
 * continue unless this Agreement is terminated pursuant to this section.  
 * This Agreement immediately terminates in the event that you materially 
 * breach any of the terms hereof.  You may terminate this Agreement at any 
 * time, with or without cause, by destroying any copies of the Software in 
 * your possession.  Upon termination, the license granted hereunder shall 
 * terminate but the Sections titled "Restrictions", "Ownership", "Disclaimer 
 * of Warranties", "Limitation of Liability", "Basis of Bargain", "Term and 
 * Termination", "Export", and "Miscellaneous" will remain in effect.  
 * 
 * Export.  The Software and related technology are subject to U.S.  export 
 * control laws and may be subject to export or import regulations in other 
 * countries.  You agree to strictly comply with all such laws and 
 * regulations and acknowledges that you have the responsibility to obtain 
 * authorization to export, re-export, or import the Software and related 
 * technology, as may be required.  You will indemnify and hold Cavium 
 * harmless from any and all claims, losses, liabilities, damages, fines, 
 * penalties, costs and expenses (including attorney's fees) arising from or 
 * relating to any breach by you of your obligations under this section.  
 * Your obligations under this section shall survive the expiration or 
 * termination of this Agreement.  
 * 
 * Miscellaneous.  Neither the rights nor the obligations arising under this 
 * Agreement are assignable by you, and any such attempted assignment or 
 * transfer shall be void and without effect.  This Agreement shall be 
 * governed by and construed in accordance with the laws of the State of 
 * California without regard to any conflicts of laws provisions that would 
 * require application of the laws of another jurisdiction.  Any action under 
 * or relating to this Agreement shall be brought in the state and federal 
 * courts located in California, with venue in the courts located in Santa 
 * Clara County and each party hereby submits to the personal jurisdiction of 
 * such courts; provided, however, that nothing herein will operate to 
 * prohibit or restrict Cavium from filing for and obtaining injunctive 
 * relief from any court of competent jurisdiction.  The United Nations 
 * Convention on Contracts for the International Sale of Goods shall not 
 * apply to this Agreement.  In the event that any provision of this 
 * Agreement is found to be contrary to law, then such provision shall be 
 * construed as nearly as possible to reflect the intention of the parties, 
 * with the other provisions remaining in full force and effect.  Any notice 
 * to you may be provided by email.  This Agreement constitutes the entire 
 * agreement between the parties and supersedes all prior or contemporaneous, 
 * agreements, understandings and communications between the parties, whether 
 * written or oral, pertaining to the subject matter hereof.  Any 
 * modifications of this Agreement must be in writing and agreed to by both 
 * parties.  
 * 
 * Copyright (c) 2003-2007, Cavium Networks. All rights reserved.
 * 
 * ***
 * 
 * OCTEON SDK License Type 4:
 * 
 * Author: Cavium Networks 
 * 
 * Contact: support@caviumnetworks.com 
 * This file is part of the OCTEON SDK
 * 
 * Copyright (c) 2007 Cavium Networks 
 * 
 * This file is free software; you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License, Version 2, as published by 
 * the Free Software Foundation. 
 * 
 * This file is distributed in the hope that it will be useful, 
 * but AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or NONINFRINGEMENT. 
 * See the GNU General Public License for more details. 
 * 
 * You should have received a copy of the GNU General Public License 
 * along with this file; if not, write to the Free Software 
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 * or visit http://www.gnu.org/licenses/. 
 * 
 * This file may also be available under a different license from Cavium. 
 * Contact Cavium Networks for more information
 ***********************license end**************************************/
/*! 
 * @file executive-config.h.template
 *
 * This file is a template for the executive-config.h file that each
 * application that uses the simple exec must provide.  Each application
 * should have an executive-config.h file in a directory named 'config'.
 * If the application uses other components, config files for those
 * components should be placed in the config directory as well.  The 
 * macros defined in this file control the configuration and functionality
 * provided by the simple executive.  Available macros are commented out
 * and documented in this file.
 */

/*
 * File version info: $Id: executive-config.h.template 31389 2008-01-24 01:37:57Z rfranz $
 *
 */
#ifndef __EXECUTIVE_CONFIG_H__
#define __EXECUTIVE_CONFIG_H__

/* Define to enable the use of simple executive DFA functions */
//#define CVMX_ENABLE_DFA_FUNCTIONS

/* Define to enable the use of simple executive packet output functions.
** For packet I/O setup enable the helper functions below. 
*/ 
//#define CVMX_ENABLE_PKO_FUNCTIONS

/* Define to enable the use of simple executive timer bucket functions. 
** Refer to cvmx-tim.[ch] for more information
*/
//#define CVMX_ENABLE_TIMER_FUNCTIONS

/* Define to enable the use of simple executive helper functions. These
** include many harware setup functions.  See cvmx-helper.[ch] for
** details.
*/
//#define CVMX_ENABLE_HELPER_FUNCTIONS

/* CVMX_HELPER_FIRST_MBUFF_SKIP is the number of bytes to reserve before
** the beginning of the packet. If necessary, override the default  
** here.  See the IPD section of the hardware manual for MBUFF SKIP 
** details.*/ 
#define CVMX_HELPER_FIRST_MBUFF_SKIP 184

/* CVMX_HELPER_NOT_FIRST_MBUFF_SKIP is the number of bytes to reserve in each
** chained packet element. If necessary, override the default here */
#define CVMX_HELPER_NOT_FIRST_MBUFF_SKIP 0

/* CVMX_HELPER_ENABLE_BACK_PRESSURE controls whether back pressure is enabled
** for all input ports. This controls if IPD sends backpressure to all ports if
** Octeon's FPA pools don't have enough packet or work queue entries. Even when
** this is off, it is still possible to get backpressure from individual
** hardware ports. When configuring backpressure, also check
** CVMX_HELPER_DISABLE_*_BACKPRESSURE below. If necessary, override the default
** here */
#define CVMX_HELPER_ENABLE_BACK_PRESSURE 1

/* CVMX_HELPER_ENABLE_IPD controls if the IPD is enabled in the helper
**  function. Once it is enabled the hardware starts accepting packets. You
**  might want to skip the IPD enable if configuration changes are need
**  from the default helper setup. If necessary, override the default here */
#define CVMX_HELPER_ENABLE_IPD 1

/* CVMX_HELPER_INPUT_TAG_TYPE selects the type of tag that the IPD assigns
** to incoming packets. */
#define CVMX_HELPER_INPUT_TAG_TYPE CVMX_POW_TAG_TYPE_ORDERED

/* The following select which fields are used by the PIP to generate
** the tag on INPUT
** 0: don't include
** 1: include */
#define CVMX_HELPER_INPUT_TAG_IPV6_SRC_IP	0
#define CVMX_HELPER_INPUT_TAG_IPV6_DST_IP   	0
#define CVMX_HELPER_INPUT_TAG_IPV6_SRC_PORT 	0
#define CVMX_HELPER_INPUT_TAG_IPV6_DST_PORT 	0
#define CVMX_HELPER_INPUT_TAG_IPV6_NEXT_HEADER 	0
#define CVMX_HELPER_INPUT_TAG_IPV4_SRC_IP	0
#define CVMX_HELPER_INPUT_TAG_IPV4_DST_IP   	0
#define CVMX_HELPER_INPUT_TAG_IPV4_SRC_PORT 	0
#define CVMX_HELPER_INPUT_TAG_IPV4_DST_PORT 	0
#define CVMX_HELPER_INPUT_TAG_IPV4_PROTOCOL	0
#define CVMX_HELPER_INPUT_TAG_INPUT_PORT	1

/* Select skip mode for input ports */
#define CVMX_HELPER_INPUT_PORT_SKIP_MODE	CVMX_PIP_PORT_CFG_MODE_SKIPL2

/* Define the number of queues per output port */
#define CVMX_HELPER_PKO_QUEUES_PER_PORT_INTERFACE0	1
#define CVMX_HELPER_PKO_QUEUES_PER_PORT_INTERFACE1	1

/* Configure PKO to use per-core queues (PKO lockless operation). 
** Please see the related SDK documentation for PKO that illustrates 
** how to enable and configure this option. */
//#define CVMX_ENABLE_PKO_LOCKLESS_OPERATION 1
//#define CVMX_HELPER_PKO_MAX_PORTS_INTERFACE0 8
//#define CVMX_HELPER_PKO_MAX_PORTS_INTERFACE1 8

/* Force backpressure to be disabled.  This overrides all other
** backpressure configuration */
#define CVMX_HELPER_DISABLE_RGMII_BACKPRESSURE 1

/* Disable the SPI4000's processing of backpressure packets and backpressure
** generation. When this is 1, the SPI4000 will not stop sending packets when
** receiving backpressure. It will also not generate backpressure packets when
** its internal FIFOs are full. */
#define CVMX_HELPER_DISABLE_SPI4000_BACKPRESSURE 1

/* CVMX_HELPER_SPI_TIMEOUT is used to determine how long the SPI initialization
** routines wait for SPI training. You can override the value using
** executive-config.h if necessary */
#define CVMX_HELPER_SPI_TIMEOUT 10

/* Select the number of low latency memory ports (interfaces) that
** will be configured.  Valid values are 1 and 2.
*/
#define CVMX_LLM_CONFIG_NUM_PORTS 2

/* Enable the fix for PKI-100 errata ("Size field is 8 too large in WQE and next
** pointers"). If CVMX_ENABLE_LEN_M8_FIX is set to 0, the fix for this errata will 
** not be enabled. 
** 0: Fix is not enabled
** 1: Fix is enabled, if supported by hardware
*/
#define CVMX_ENABLE_LEN_M8_FIX  1

#if defined(CVMX_ENABLE_HELPER_FUNCTIONS) && !defined(CVMX_ENABLE_PKO_FUNCTIONS)
#define CVMX_ENABLE_PKO_FUNCTIONS
#endif

/* Enable setting up of TLB entries to trap NULL pointer references */
#define CVMX_CONFIG_NULL_POINTER_PROTECT	1

/* Enable debug and informational printfs */
#define CVMX_CONFIG_ENABLE_DEBUG_PRINTS 	1

/* Executive resource descriptions provided in cvmx-resources.config */
#include "cvmx-resources.config"

#endif
