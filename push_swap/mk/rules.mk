all: $(NAME)
	@echo "$(GREEN)✅ Compilation completed: $(NAME)$(RESET)"

bonus: $(BONUS_NAME)
	@echo "$(GREEN)✅ Bonus compilation completed: $(BONUS_NAME)$(RESET)"

$(NAME): $(OBJECTS)
	@echo "$(BLUE)🔗 Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS)
	@echo "$(CYAN)🚀 $(NAME) ready.$(RESET)"

$(BONUS_NAME): $(BONUS_OBJECTS)
	@echo "$(BLUE)🔗 Linking $(BONUS_NAME)...$(RESET)"
	@$(CC) $(CFLAGS) -o $(BONUS_NAME) $(BONUS_OBJECTS)
	@echo "$(CYAN)🚀 $(BONUS_NAME) ready.$(RESET)"

$(OBJ_DIR)/%.o: %.c
	@echo "$(YELLOW)🔧 Compiling $<...$(RESET)"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

$(BONUS_OBJ_DIR)/%.o: %.c
	@echo "$(YELLOW)🔧 Compiling $<...$(RESET)"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(BONUS_INC) -MMD -MP -c $< -o $@

clean:
	@echo "$(RED)🧹 Removing object files...$(RESET)"
	@$(RM) -r $(OBJ_DIR) $(BONUS_OBJ_DIR)
	@echo "$(RED)✔️ Clean done.$(RESET)"

fclean: clean
	@echo "$(RED)🧨 Removing binaries...$(RESET)"
	@$(RM) $(NAME) $(BONUS_NAME)
	@echo "$(RED)✔️ Fclean done.$(RESET)"

re: fclean
	@$(MAKE) --no-print-directory all

-include $(DEPS)

.PHONY: all bonus clean fclean re
