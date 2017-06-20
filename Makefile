#编译下面指定的项目
PROJECT_APPS=test


.PHONY:build_all
.PHONY:clean
all:build_all 
	@echo "Done!"

build_all:
	@echo "Making all projects..."
	@$(foreach n, $(PROJECT_APPS), cd apps/$(n) && make && cd ${CURDIR})

clean:
	@echo "Cleaning all projects..."
	@$(foreach n, $(PROJECT_APPS), cd apps/$(n) && make clean && cd ${CURDIR})