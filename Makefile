SUBDIRS:=wireless_tools lib/ul_lib busybox-1.00-pre8-rtl udhcp-0.9.8 boa-0.94.13/src iptables-1.2.7a bridge-utils/libbridge bridge-utils/brctl miniupnpd-20090605 smtpclient igmpproxy.rtl captcha miniupnpc-1.6

PHONY := all $(SUBDIRS)
all: $(SUBDIRS)
	@echo -e "\nDone!\n"

$(SUBDIRS):
	echo "========================================================================"
	echo -e "\033[32m$$i\033[0m"
	echo "------------------------------------------------------------------------"
	$(MAKE) -C $@

PHONY += clean
clean:
	for i in $(SUBDIRS) ; do \
		echo -e "\033[31m$$i\033[0m"; \
		$(MAKE) -C $$i clean; \
	done

.PHONY: $(PHONY)
