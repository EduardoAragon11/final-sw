export const Roles = {
  ADMIN: "Admin",
  USER: "User"
} as const;

export type Role = typeof Roles[keyof typeof Roles];
