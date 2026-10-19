all: $(NAME)
	@echo "$(GREEN)✅ Compilation completed: $(NAME)$(RESET)"

$(NAME): $(OBJECTS)
	@echo "$(BLUE)🔗 Linking $(NAME)...$(RESET)"
	@$(CXX) $(CXXFLAGS) -o $(NAME) $(OBJECTS)
	@echo "$(CYAN)🚀 $(NAME) ready.$(RESET)"

$(OBJ_DIR)/%.o: %.cpp
	@echo "$(YELLOW)🔧 Compiling $<...$(RESET)"
	@mkdir -p $(dir $@)
	@$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

clean:
	@echo "$(RED)🧹 Removing object files...$(RESET)"
	@$(RM) -r $(OBJ_DIR)
	@echo "$(RED)✔️ Clean done.$(RESET)"

fclean: clean
	@echo "$(RED)🧨 Removing binary...$(RESET)"
	@$(RM) $(NAME)
	@echo "$(RED)✔️ Fclean done.$(RESET)"

re: fclean
	@$(MAKE) --no-print-directory all

-include $(DEPS)

.PHONY: all clean fclean re
