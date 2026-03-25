all: $(NAME)
	@echo "$(GREEN)✅ Build finished: $(NAME)$(RESET)"

bonus: $(BONUS_NAME)
	@echo "$(GREEN)✅ Bonus build finished: $(BONUS_NAME)$(RESET)"

$(OBJ_DIR):
	@$(MKDIR) $(OBJ_DIR)
	@echo "$(CYAN)📁 Created obj directory.$(RESET)"

$(BONUS_OBJ_DIR):
	@$(MKDIR) $(BONUS_OBJ_DIR)
	@echo "$(CYAN)📁 Created obj_bonus directory.$(RESET)"

$(NAME): $(OBJ_DIR) $(OBJECTS)
	@echo "$(BLUE)🔗 Linking push_swap...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
	@echo "$(GREEN)✨ $(NAME) created successfully!$(RESET)"

$(BONUS_NAME): $(BONUS_OBJ_DIR) $(BONUS_OBJECTS)
	@echo "$(BLUE)🔗 Linking checker...$(RESET)"
	@$(CC) $(CFLAGS) -I$(BONUS_DIR) $(BONUS_OBJECTS) -o $(BONUS_NAME)
	@echo "$(GREEN)✨ $(BONUS_NAME) created successfully!$(RESET)"

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@echo "$(YELLOW)🔧 Compiling: $<...$(RESET)"
	@$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(OPS_DIR)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)🔧 Compiling: $<...$(RESET)"
	@$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(UTILS_DIR)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)🔧 Compiling: $<...$(RESET)"
	@$(CC) -c $(CFLAGS) $< -o $@

$(OBJ_DIR)/%.o: $(SORT_DIR)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)🔧 Compiling: $<...$(RESET)"
	@$(CC) -c $(CFLAGS) $< -o $@

$(BONUS_OBJ_DIR)/%.o: $(BONUS_DIR)/%.c | $(BONUS_OBJ_DIR)
	@echo "$(YELLOW)🔧 Compiling bonus: $<...$(RESET)"
	@$(CC) -c $(CFLAGS) -I$(BONUS_DIR) $< -o $@

$(BONUS_OBJ_DIR)/%.o: $(BONUS_DIR)/utils/%.c | $(BONUS_OBJ_DIR)
	@echo "$(YELLOW)🔧 Compiling bonus: $<...$(RESET)"
	@$(CC) -c $(CFLAGS) -I$(BONUS_DIR) $< -o $@

$(BONUS_OBJ_DIR)/%.o: $(UTILS_DIR)/%.c | $(BONUS_OBJ_DIR)
	@echo "$(YELLOW)🔧 Compiling bonus: $<...$(RESET)"
	@$(CC) -c $(CFLAGS) -I$(BONUS_DIR) $< -o $@

$(BONUS_OBJ_DIR)/%.o: $(OPS_DIR)/%.c | $(BONUS_OBJ_DIR)
	@echo "$(YELLOW)🔧 Compiling bonus: $<...$(RESET)"
	@$(CC) -c $(CFLAGS) -I$(BONUS_DIR) $< -o $@

clean:
	@echo "$(RED)🧹 Removing object files...$(RESET)"
	@$(RM_RF) $(OBJ_DIR) $(BONUS_OBJ_DIR)
	@echo "$(RED)✔️ Clean complete.$(RESET)"

fclean: clean
	@echo "$(RED)🧨 Removing executables...$(RESET)"
	@$(RM) $(NAME) $(BONUS_NAME)
	@echo "$(RED)✔️ Full clean complete.$(RESET)"

re: fclean all

.PHONY: all bonus clean fclean re
